#pragma once

namespace dsr
{
	class NotSupportedException : public std::runtime_error
	{
	public:
		explicit NotSupportedException(const char* msg)
			: std::runtime_error(msg) {};

		explicit NotSupportedException(const std::string& msg)
			: std::runtime_error(msg) {};
	};
}
