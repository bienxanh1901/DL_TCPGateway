#include "Networking/TCPServer.h"
#include <cstdio>
#include <mongoose.h>

TCPServer::TCPServer(const std::string& url)
    : MongooseConnection()
    , m_url(url)
{
}

void TCPServer::start()
{
    if (m_state != StartState) {
        m_conn = mg_listen(&m_mgr, m_url.c_str(), &TCPServer::eventHandler, this);
    }
}

void TCPServer::onOpening(mg_connection* conn)
{
    m_state = StartState;
}

void TCPServer::onConnectionClosed(mg_connection* conn)
{
    if (m_conn == conn) {
        m_state = StopState;
        m_conn = nullptr;
    }
}
