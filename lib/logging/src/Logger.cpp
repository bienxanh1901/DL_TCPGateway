#include "Logging/Logger.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>

Logger::Logger(std::string service, LogSinkType type, spdlog::level::level_enum level)
{
    switch (type) {
    case File: {
        std::string filename = service + ".log";
        m_log = spdlog::basic_logger_mt(service, filename, false);
        break;
    }
    case System:
        m_log = spdlog::syslog_logger_mt(service, service, LOG_PID);
        break;
    default:
        m_log = spdlog::stdout_color_mt(service);
        break;
    }

    m_log->set_level(level);
}
