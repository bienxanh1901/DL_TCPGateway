#include "Networking/ConnectionObserver.h"
#include "Networking/Utils.h"
#include <mongoose.h>

void ConnectionObserver::onOpening(mg_connection* conn)
{
    MG_INFO(("Client is openning connection %s", addrString(conn->loc).c_str()));
}

void ConnectionObserver::onConnectionConnected(mg_connection* conn)
{
    MG_INFO(("Client connected %s", addrString(conn->loc).c_str()));
}

void ConnectionObserver::onConnectionAccepted(mg_connection* conn)
{
    MG_INFO(("Server accepted connection %s", addrString(conn->loc).c_str()));
}

void ConnectionObserver::onConnectionClosed(mg_connection* conn)
{
    MG_INFO(("Connection Closed %s", addrString(conn->loc).c_str()));
}

void ConnectionObserver::onMessageReceived(mg_connection* conn)
{
    MG_INFO(("Message Received %s", addrString(conn->loc).c_str()));
}

void ConnectionObserver::onMessageSend(mg_connection* conn)
{
    MG_INFO(("Messeage Send %s", addrString(conn->loc).c_str()));
}

void ConnectionObserver::onError(mg_connection* conn, void* eventData)
{
    MG_INFO(("Connection error %s", addrString(conn->loc).c_str()));
}

void ConnectionObserver::onPolling(void* eventData)
{
    MG_INFO(("MGR polling"));
}
