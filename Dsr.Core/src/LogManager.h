#pragma once

#include <map>
#include <string>

#include "SpdLoggerFactory.h"

namespace dsr
{
	class LogManager
	{
	public:
		static std::shared_ptr<spdlog::logger> GetLogger(std::string moduleName);
	private:
		static std::map<std::string, std::shared_ptr<spdlog::logger>> s_loggers;
		static std::mutex s_m_loggers;
	};
}
