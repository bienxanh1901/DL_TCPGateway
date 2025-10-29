#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "MongooseConnection.h"
#include <string>

class TCPClient : public MongooseConnection
{
public:
    TCPClient(const std::string& url);
    void start();
    void stop();
    virtual void onConnectionConnected(struct mg_connection* conn) override;
    virtual void onConnectionClosed(struct mg_connection* conn) override;

protected:
    std::string m_url;
};

#endif // TCPCLIENT_H
