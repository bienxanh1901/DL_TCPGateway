#include "Logging/ServiceLogManager.h"
#include "spdlog/common.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <string>

void ServiceLogManager::init(const std::string& serviceName, const std::string& logDir)
{
    const std::string baseDir = logDir + serviceName;
    const std::string info = baseDir + "/info.log";
    const std::string all = baseDir + "/all.log";
    const std::string err = baseDir + "/err.log";
    const std::string warn = baseDir + "/warn.log";
    const std::string debug = baseDir + "/debug.log";

    m_logs["info"] = basic_logger_mt("info", info);
    m_logs["info"]->set_level(spdlog::level::info);
    m_logs["all"] = basic_logger_mt("all", all);
    m_logs["all"]->set_level(spdlog::level::trace);
    m_logs["err"] = basic_logger_mt("err", err);
    m_logs["err"]->set_level(spdlog::level::err);
    m_logs["warn"] = basic_logger_mt("warn", warn);
    m_logs["warn"]->set_level(spdlog::level::warn);
    m_logs["debug"] = basic_logger_mt("debug", debug);
    m_logs["debug"]->set_level(spdlog::level::debug);
    m_isReady = true;
}

