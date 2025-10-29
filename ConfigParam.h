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

    int serverPort = 8888;
    std::string url;

private:
    ConfigParam();

    std::string getEnv(const std::string& key, const std::string& defaultVal = "");
};

#endif // CONFIG_PARAM_H
