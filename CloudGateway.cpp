#include "CloudGateway.h"
#include "ConfigParam.h"
#include <Logging/LogManager.h>
#include <Logging/Logger.h>
#include <mongoose.h>

CloudGateway::CloudGateway()
    : m_server(ConfigParam::instance()->url)
{
    mg_log_set(MG_LL_INFO);
    LogManager::instance();
}

void CloudGateway::start()
{
    m_server.start();
    while (m_server.state() != TCPServer::StartState) {
        LogManager::instance()->info("Waiting...");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    LogManager::instance()->info("Server Started");

    while (true) {
        LogManager::instance()->info("Current connections: {}", m_server.numberClients());
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }

    LogManager::instance()->info("Server Stopped");
}
