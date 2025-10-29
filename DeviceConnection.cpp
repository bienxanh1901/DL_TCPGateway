#include "DeviceConnection.h"
#include <VMCommon/Utils.h>
#include <Logging/LogManager.h>
#include <DataLoggerProtocol/GeneralResponseMessageBody.h>
#include <DataLoggerProtocol/DataUploadMessageBody.h>
#include <DataLoggerProtocol/LoginMessageBody.h>
#include <DataLoggerProtocol/Message.h>
#include <DataLoggerProtocol/MessageCode.h>
#include <DataLoggerProtocol/ResponseCode.h>
#include <cstdint>
#include <mongoose.h>
#include <sstream>
#include <string>
#include <utility>
#include <Networking/Utils.h>

DeviceConnection::DeviceConnection(mg_connection* conn, std::string addr)
    : m_addr(std::move(addr))
    , m_conn(conn)
{
    LogManager::instance()->info("Device connected {}", m_addr);
}

DeviceConnection::~DeviceConnection()
{
    LogManager::instance()->info("Device disconnected {}", m_addr);
}

void DeviceConnection::handleIncommingMessage(ByteArray& data)
{
    int pos = 0;
    int pos2 = 0;
    Message msg;
    std::stringstream ss;

    while (true) {
        for (; pos < data.size() && data[pos] != Message::ProtocolSign; pos++)
            ;

        if (pos == data.size()) {
            break;
        }

        for (pos2 = pos + 1; pos2 < data.size() && data[pos2] != Message::ProtocolSign; pos2++)
            ;

        if (pos2 == data.size()) {
            break;
        }

        pos2++;

        ByteArray const sub(data.data() + pos, data.data() + pos2);
        printHexArray(sub, ss);
        pos = pos2;

        msg.parse(sub);

        if (!msg.isValid()) {
            LogManager::instance()->warn("{} << [RECV INVALID] << {}", m_id, ss.str());
            continue;
        }

        LogManager::instance()->info("{} << [RECV] << {}", m_id, msg.toJson().dump());
        LogManager::instance()->debug("{} << [RECV] << {} << {}", m_id, MessageCodeStr(msg.header().code()), ss.str());
        m_seq = msg.header().seq() + 1;

        ss.clear();

        switch (m_state) {
        case ConnectedState:
            handleConnectState(msg);
            break;
        case CommunicationState:
            handleCommunicationState(msg);
            break;
        default:
            break;
        }
    }
}

void DeviceConnection::onMessageSend()
{
    LogManager::instance()->info("{} << [SEND SUCCESS]", m_id);

    switch (m_state) {
    case LoginState:
        m_state = CommunicationState;
        break;
    default:
        break;
    }
}

bool DeviceConnection::send(Message& msg)
{
    std::stringstream ss;
    ByteArray data(msg.package());
    printHexArray(data, ss);
    LogManager::instance()->info("{} << [SEND] << {} ", m_id, msg.toJson().dump());
    LogManager::instance()->debug("{} << [SEND] << {} << {}", m_id, MessageCodeStr(msg.header().code()), ss.str());

    if (data.empty()) {
        return false;
    }

    return mg_send(m_conn, data.data(), data.size());
}

bool DeviceConnection::handleConnectState(Message& msg)
{
    if (msg.header().code() == DeviceLoginMessage) {
        return onLoginMessage(msg);
    }

    return false;
}

bool DeviceConnection::handleCommunicationState(Message& msg)
{
    bool result = true;

    switch (msg.header().code()) {
    case HeartbeatMessage:
        result = onTerminalHeartBeat(msg);
        break;
    case DataUploadMessage:
        result = onDataUploadDataMessage(msg);
        break;
    default:
        break;
    }

    return result;
}

bool DeviceConnection::onLoginMessage(Message& msg)
{
    auto* body = dynamic_cast<LoginMessageBody*>(msg.body());
    m_id = body->id();
    m_state = LoginState;
    return generalResponse(msg.header().seq());
}

bool DeviceConnection::onTerminalHeartBeat(Message& msg)
{
    m_isAlive = true;
    return generalResponse(msg.header().seq(), Success);
}

bool DeviceConnection::onDataUploadDataMessage(Message& msg)
{
    auto* body = dynamic_cast<DataUploadMessageBody*>(msg.body());

    return generalResponse(msg.header().seq(), Success);
}

bool DeviceConnection::generalResponse(uint16_t seq, ResponseCode response)
{
    MessageHeader const header(seq + 1, MessageCode::GeneralResponseMessage);
    auto* body(new GeneralResponseMessageBody(seq, response));
    Message msg(header, body);

    return send(msg);
}

DeviceConnection::States DeviceConnection::state() const
{
    return m_state;
}

mg_connection* DeviceConnection::conn() const
{
    return m_conn;
}

std::string DeviceConnection::addr() const
{
    return m_addr;
}

bool DeviceConnection::isAlive() const
{
    return m_isAlive.load();
}

void DeviceConnection::setIsAlive(const bool& newIsAlive)
{
    m_isAlive.store(newIsAlive);
}
