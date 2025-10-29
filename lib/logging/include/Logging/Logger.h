#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <spdlog/common.h>
#include <spdlog/logger.h>

using namespace spdlog;

class Logger
{
public:
    enum LogSinkType : uint8_t
    {
        Console = 0,
        File,
        System
    };

    Logger(std::string service, LogSinkType type = Console, level::level_enum level = level::level_enum::info);

    template<typename... Args>
    void debug(format_string_t<Args...> fmt, Args&&... args)
    {
        m_log->log(level::debug, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void info(format_string_t<Args...> fmt, Args&&... args)
    {
        m_log->log(level::info, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void warn(format_string_t<Args...> fmt, Args&&... args)
    {
        m_log->log(level::warn, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void error(format_string_t<Args...> fmt, Args&&... args)
    {
        m_log->log(level::err, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void critical(format_string_t<Args...> fmt, Args&&... args)
    {
        m_log->log(level::critical, fmt, std::forward<Args>(args)...);
    }

private:
    std::shared_ptr<logger> m_log;
};
#endif // LOGGER_H
