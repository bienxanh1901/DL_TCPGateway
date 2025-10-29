#include "Logging/LogManager.h"
#include "spdlog/common.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

LogManager::LogManager()
{
    m_logs["console"] = stdout_color_mt("console");
    m_logs["console"]->set_level(spdlog::level::info);
    m_logs["info"] = daily_logger_mt("info", "logs/info.log");
    m_logs["info"]->set_level(spdlog::level::info);
    m_logs["all"] = daily_logger_mt("all", "logs/all.log");
    m_logs["all"]->set_level(spdlog::level::trace);
    m_logs["err"] = daily_logger_mt("err", "logs/error.log");
    m_logs["err"]->set_level(spdlog::level::err);
    m_logs["warn"] = daily_logger_mt("warn", "logs/warn.log");
    m_logs["warn"]->set_level(spdlog::level::warn);
    m_logs["debug"] = daily_logger_mt("debug", "logs/debug.log");
    m_logs["debug"]->set_level(spdlog::level::debug);
}
