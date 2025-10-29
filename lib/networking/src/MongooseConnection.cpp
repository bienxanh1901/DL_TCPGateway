#include "Networking/MongooseConnection.h"
#include <cstdio>
#include <mongoose.h>
#include <thread>

MongooseConnection::MongooseConnection()
{
    mg_mgr_init(&m_mgr);
    std::thread pollingThread([this] { poll(); });
    pollingThread.detach();
}

MongooseConnection::~MongooseConnection()
{
    mg_mgr_free(&m_mgr);
}

void MongooseConnection::send(uint8_t* data, int size)
{
    send(m_conn, data, size);
}

void MongooseConnection::send(mg_connection* conn, uint8_t* data, int size)
{
    mg_send(conn, data, size);
}

MongooseConnection::State MongooseConnection::state()
{
    return m_state.load();
}

void MongooseConnection::poll()
{
    while (true) {
        mg_mgr_poll(&m_mgr, 100);
    }
}

void MongooseConnection::eventHandler(mg_connection* conn, int event, void* eventData)
{
    auto* self = (MongooseConnection*)(conn->fn_data);

    switch (event) {
    case MG_EV_OPEN:
        self->onOpening(conn);
        break;
    case MG_EV_CONNECT:
        self->onConnectionConnected(conn);
        break;
    case MG_EV_ACCEPT:
        self->onConnectionAccepted(conn);
        break;
    case MG_EV_READ:
        self->onMessageReceived(conn);
        break;
    case MG_EV_WRITE:
        self->onMessageSend(conn);
        break;
    case MG_EV_CLOSE:
        self->onConnectionClosed(conn);
        break;
    case MG_EV_ERROR:
        self->onError(conn, eventData);
        break;
    case MG_EV_POLL:
        // self->onPolling(eventData);
        break;
    default:
        break;
    }
}

