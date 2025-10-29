#ifndef CLOUDGATEWAY_H
#define CLOUDGATEWAY_H

#include "DeviceConnection.h"
#include <Networking/ConnectionObserver.h>
#include <Networking/TCPServerTemplate.h>
#include <memory>

template class TCPServerTemplate<DeviceConnection>;

class CloudGateway
{
public:
    static CloudGateway* instance()
    {
        static std::unique_ptr<CloudGateway> instance;

        if (!instance) {
            instance.reset(new CloudGateway());
        }

        return instance.get();
    }

    void start();

private:
    CloudGateway();

    ConnectionObserver m_observer;
    TCPServerTemplate<DeviceConnection> m_server;
};

#endif // CLOUDGATEWAY_H
