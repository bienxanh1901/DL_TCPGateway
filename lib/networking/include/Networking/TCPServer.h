#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "MongooseConnection.h"
#include <string>

class TCPServer : public MongooseConnection
{
public:
    TCPServer(const std::string& url);
    void start();
    virtual void onOpening(struct mg_connection* conn) override;
    virtual void onConnectionClosed(struct mg_connection* conn) override;

protected:
    std::string m_url;
};

#endif // TCP_SERVER_H
