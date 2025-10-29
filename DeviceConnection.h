#ifndef DEVICECONNECTION_H
#define DEVICECONNECTION_H

#include <DataLoggerProtocol//Utils.h>
#include <DataLoggerProtocol/Message.h>
#include <DataLoggerProtocol/ResponseCode.h>
#include <atomic>
#include <cstdint>
#include <mongoose.h>
#include <string>

class DeviceConnection
{
public:
    enum States : uint8_t
    {
        InitState = 0,
        ConnectedState,
        LoginState,
        CommunicationState,
        DisconnectedState,
        ErrorState
    };

    DeviceConnection(mg_connection* conn, std::string addr);
    ~DeviceConnection();
    void handleIncommingMessage(ByteArray& data);
    void onMessageSend();
    bool isAlive() const;
    void setIsAlive(const bool& newIsAlive);
    std::string addr() const;
    mg_connection* conn() const;
    States state() const;

private:
    bool send(Message& msg);
    bool handleConnectState(Message& msg);
    bool handleCommunicationState(Message& msg);
    bool onLoginMessage(Message& msg);
    bool onTerminalHeartBeat(Message& msg);
    bool onDataUploadDataMessage(Message& msg);
    bool generalResponse(uint16_t seq, ResponseCode response = ResponseCode::Success);

    States m_state = ConnectedState;
    std::string m_addr;
    std::string m_id;
    uint16_t m_seq;
    mg_connection* m_conn;
    std::atomic<bool> m_isAlive = false;
};

#endif // DEVICECONNECTION_H
