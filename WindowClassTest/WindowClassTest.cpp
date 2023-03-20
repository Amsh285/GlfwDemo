

#include <iostream>

#include "LogManager.h"
#include "WindowTestApplication.h"

int main()
{
	std::shared_ptr<spdlog::logger> logger = dsr::LogManager::GetLogger("main");

	std::unique_ptr<WindowTestApplication> application = std::make_unique<WindowTestApplication>();
	dsr::ApplicationExitCodes exitCode = application->Run();

	logger->info("Shutting down Application: (Message: {0}) (Code: {1}).", exitCode.Message, exitCode.Code);
	return exitCode.Code;
}