#ifndef TCPSERVERTEMPLATE_H
#define TCPSERVERTEMPLATE_H

#include "TCPServer.h"
#include "Utils.h"
#include "mongoose.h"
#include <string>
#include <unordered_map>
#include <vector>

template<class T>
class TCPServerTemplate : public TCPServer
{
public:
    TCPServerTemplate(const std::string& url)
        : TCPServer(url)
    {
    }

    ~TCPServerTemplate() override
    {
        for (auto const& client : m_clients) {
            delete client.second;
        }

        m_clients.clear();

        MongooseConnection::~MongooseConnection();
    }

    void onConnectionAccepted(struct mg_connection* conn) override
    {
        std::string addr(addrString(conn->rem));
        if (m_clients.find(addr) == m_clients.end()) {
            auto* client = new T(conn, addr);
            m_conns[addr] = conn;
            m_clients[addr] = client;
            m_numberClients = m_conns.size();
        }
    };
    void onConnectionClosed(struct mg_connection* conn) override
    {
        std::string addr(addrString(conn->rem));
        typename std::unordered_map<std::string, T*>::iterator it = m_clients.find(addr);
        if (it != m_clients.end()) {
            delete it->second;
            m_clients.erase(addr);
            m_conns.erase(addr);
            m_numberClients = m_conns.size();
        }
    }

    void onMessageReceived(struct mg_connection* conn) override
    {
        std::string addr(addrString(conn->rem));
        typename std::unordered_map<std::string, T*>::iterator it = m_clients.find(addr);
        if (it != m_clients.end()) {
            struct mg_iobuf* buff = &conn->recv;
            std::vector<uint8_t> data(buff->buf, buff->buf + buff->len);
            buff->len = 0;
            it->second->handleIncommingMessage(data);
        }
    }

    void onMessageSend(struct mg_connection* conn) override
    {
        std::string addr(addrString(conn->rem));
        typename std::unordered_map<std::string, T*>::iterator it = m_clients.find(addr);
        if (it != m_clients.end()) {
            it->second->onMessageSend();
        }
    }

    void disconnect(const std::string& addr)
    {
        std::unordered_map<std::string, struct mg_connection*>::iterator it = m_conns.find(addr);
        if (it != m_conns.end()) {
            it->second->is_draining = 1;
        }
    }

    T* client(const std::string& addr)
    {
        typename std::unordered_map<std::string, T*>::iterator it = m_clients.find(addr);
        if (it != m_clients.end()) {
            return m_clients[addr];
        } else {
            return nullptr;
        }
    }

    int numberClients() const
    {
        return m_numberClients;
    }

private:
    std::unordered_map<std::string, struct mg_connection*> m_conns;
    std::unordered_map<std::string, T*> m_clients;
    int m_numberClients = 0;
};

#endif // TCPSERVERTEMPLATE_H
