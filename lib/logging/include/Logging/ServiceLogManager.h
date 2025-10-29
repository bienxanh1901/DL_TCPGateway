#ifndef SERVICELOGMANAGER_H
#define SERVICELOGMANAGER_H

#include <memory>
#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <string>
#include <unordered_map>

using namespace spdlog;

class ServiceLogManager
{
public:
    static ServiceLogManager* instance()
    {
        static std::unique_ptr<ServiceLogManager> instance;

        if (!instance) {
            instance.reset(new ServiceLogManager());
        }

        return instance.get();
    }

    void init(const std::string& serviceName, const std::string& logDir = "/var/log/");

    template<typename... Args>
    void debug(format_string_t<Args...> fmt, Args&&... args)
    {
        m_logs["debug"]->log(level::debug, fmt, std::forward<Args>(args)...);
        m_logs["all"]->log(level::debug, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void info(format_string_t<Args...> fmt, Args&&... args)
    {
        m_logs["info"]->log(level::info, fmt, std::forward<Args>(args)...);
        m_logs["all"]->log(level::info, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void warn(format_string_t<Args...> fmt, Args&&... args)
    {
        m_logs["warn"]->log(level::warn, fmt, std::forward<Args>(args)...);
        m_logs["all"]->log(level::warn, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void error(format_string_t<Args...> fmt, Args&&... args)
    {
        m_logs["err"]->log(level::err, fmt, std::forward<Args>(args)...);
        m_logs["all"]->log(level::err, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void critical(format_string_t<Args...> fmt, Args&&... args)
    {
        m_logs["err"]->log(level::critical, fmt, std::forward<Args>(args)...);
        m_logs["all"]->log(level::critical, fmt, std::forward<Args>(args)...);
    }

private:
    ServiceLogManager() = default;
    std::unordered_map<std::string, std::shared_ptr<logger>> m_logs;
    bool m_isReady = false;
};

#endif // SERVICELOGMANAGER_H
