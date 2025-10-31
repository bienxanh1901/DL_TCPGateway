#ifndef CONFIG_PARAM_H
#define CONFIG_PARAM_H

#include <memory>
#include <string>

class ConfigParam
{
public:
    static ConfigParam* instance()
    {
        static std::unique_ptr<ConfigParam> instance;

        if (!instance) {
            instance.reset(new ConfigParam());
        }

        return instance.get();
    }

    std::string url() const;

    std::string kafkaBrokers() const;

    std::string kafkaTopic() const;

    std::string kafkaUsername() const;

    std::string kafkaPassword() const;

private:
    ConfigParam();
    std::string getEnv(const std::string& key, const std::string& defaultVal = "");
    int m_serverPort = 8888;
    std::string m_url;
    std::string m_kafkaBrokers;
    std::string m_kafkaTopic;
    std::string m_kafkaUsername;
    std::string m_kafkaPassword;
};

#endif // CONFIG_PARAM_H
