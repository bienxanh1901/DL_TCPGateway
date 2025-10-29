#include "ConfigParam.h"
#include <cstdlib>
#include <string>

namespace {
#define SERVER_PORT_DEFAULT "8888"
}

ConfigParam::ConfigParam()
{
    serverPort = std::stoi(getEnv("SERVER_PORT", SERVER_PORT_DEFAULT), nullptr);
    url = "tcp://0.0.0.0:" + std::to_string(serverPort);
}

std::string ConfigParam::getEnv(const std::string& key, const std::string& defaultVal)
{
    char* val = std::getenv(key.c_str());
    return val == nullptr ? defaultVal : std::string(val);
}
