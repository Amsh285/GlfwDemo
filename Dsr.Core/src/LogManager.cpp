
#include "dsrpch.h"
#include "LogManager.h"

namespace dsr
{
	std::map<std::string, std::shared_ptr<spdlog::logger>> LogManager::s_loggers;
	std::mutex LogManager::s_m_loggers;

	std::shared_ptr<spdlog::logger> LogManager::GetLogger(std::string moduleName)
	{
		std::lock_guard<std::mutex> m(s_m_loggers);

		if (s_loggers.find(moduleName) != s_loggers.end())
			return s_loggers[moduleName];
		else
		{
			s_loggers[moduleName] = dsr::loggerfactory::CreateLogger(moduleName);
			return s_loggers[moduleName];
		}
	}
}
