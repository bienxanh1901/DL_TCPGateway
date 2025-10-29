#ifndef CONNECTION_OBSERVER_H
#define CONNECTION_OBSERVER_H

#include "mongoose.h"

class ConnectionObserver
{
public:
    virtual void onOpening(struct mg_connection* conn);
    virtual void onConnectionConnected(struct mg_connection* conn);
    virtual void onConnectionAccepted(struct mg_connection* conn);
    virtual void onConnectionClosed(struct mg_connection* conn);
    virtual void onMessageReceived(struct mg_connection* conn);
    virtual void onMessageSend(struct mg_connection* conn);
    virtual void onError(struct mg_connection* conn, void* eventData);
    virtual void onPolling(void* eventData);
};

#endif // CONNECTION_OBSERVER_H
