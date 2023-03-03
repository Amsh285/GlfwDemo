#pragma once

#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"


namespace dsr
{
	namespace loggerfactory
	{
		static std::shared_ptr<spdlog::logger> CreateLogger(std::string module)
		{
			auto max_size = 1048576 * 10;
			auto max_files = 3;

			auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			console_sink->set_level(spdlog::level::info);
			console_sink->set_pattern("[%Y-%m-%d %T.%e] [%n] [%^%l%$] %v");

			auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/log.txt", max_size, max_files);
			rotating_sink->set_level(spdlog::level::trace);
			rotating_sink->set_pattern("[%Y-%m-%d %T.%e] [%n] [%^%l%$] %v");

			spdlog::logger* ptr = new spdlog::logger(module, { rotating_sink, console_sink });
			return std::shared_ptr<spdlog::logger>(ptr);
		}
	}
}