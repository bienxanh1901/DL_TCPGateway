#ifndef MONGOOSECONNECTION_H
#define MONGOOSECONNECTION_H

#include "ConnectionObserver.h"
#include "mongoose.h"
#include <atomic>

class MongooseConnection : public ConnectionObserver
{
public:
    enum State : uint8_t
    {
        InitState = 0,
        StartState,
        StopState
    };
    MongooseConnection();
    virtual ~MongooseConnection();

    void send(uint8_t* data, int size);
    void send(struct mg_connection* conn, uint8_t* data, int size);
    State state();

protected:
    static void eventHandler(struct mg_connection* conn, int event, void* eventData);
    struct mg_mgr m_mgr;
    struct mg_connection* m_conn = nullptr;
    std::atomic<State> m_state = InitState;

private:
    void poll();
};

#endif // MONGOOSECONNECTION_H
