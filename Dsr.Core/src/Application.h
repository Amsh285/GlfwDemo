#pragma once

namespace dsr
{
	struct ApplicationExitCodes
	{
		static int SuccessExitCode;
		static ApplicationExitCodes Success();

		std::string Message;
		int Code;

		ApplicationExitCodes(const std::string& message, const int& code)
			: Message(message), Code(code) {}
	};

	class Application
	{
	public:
		virtual ApplicationExitCodes Run() = 0;
		virtual ~Application() {}
	};
}
