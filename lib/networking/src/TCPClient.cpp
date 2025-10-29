#include "Networking/TCPClient.h"
#include <cstdio>
#include <mongoose.h>

TCPClient::TCPClient(const std::string& url)
    : MongooseConnection()
    , m_url(url)
{
}

void TCPClient::start()
{
    if (m_state != StartState) {
        m_conn = mg_connect(&m_mgr, m_url.c_str(), &TCPClient::eventHandler, this);
    }
}

void TCPClient::stop()
{
    if (m_state == StartState) {
        m_conn->is_draining = 1;
    }
}

void TCPClient::onConnectionConnected(mg_connection* conn)
{
    m_state = StartState;
}

void TCPClient::onConnectionClosed(mg_connection* conn)
{
    if (conn == m_conn) {
        m_state = StopState;
        m_conn = nullptr;
    }
}
