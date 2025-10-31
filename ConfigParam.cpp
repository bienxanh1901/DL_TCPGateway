#include "ConfigParam.h"
#include <cstdlib>
#include <string>

namespace {
#define SERVER_PORT_DEFAULT "8888"
#define KAFKA_TOPIC_DEFAULT "DataLogger"
}

ConfigParam::ConfigParam()
{
    m_serverPort = std::stoi(getEnv("SERVER_PORT", SERVER_PORT_DEFAULT), nullptr);
    m_url = "tcp://0.0.0.0:" + std::to_string(m_serverPort);
    m_kafkaBrokers = getEnv("KAFKA_BROKERS");
    m_kafkaTopic = getEnv("KAFKA_TOPIC", KAFKA_TOPIC_DEFAULT);
    m_kafkaUsername = getEnv("KAFKA_USERNAME");
    m_kafkaPassword = getEnv("KAFKA_PASSWORD");
}

std::string ConfigParam::getEnv(const std::string& key, const std::string& defaultVal)
{
    char* val = std::getenv(key.c_str());
    return val == nullptr ? defaultVal : std::string(val);
}

std::string ConfigParam::kafkaPassword() const
{
    return m_kafkaPassword;
}

std::string ConfigParam::kafkaUsername() const
{
    return m_kafkaUsername;
}

std::string ConfigParam::kafkaTopic() const
{
    return m_kafkaTopic;
}

std::string ConfigParam::kafkaBrokers() const
{
    return m_kafkaBrokers;
}

std::string ConfigParam::url() const
{
    return m_url;
}
