#pragma once

#include <stdexcept>

namespace dsr
{
	class InvalidOperationException : public std::runtime_error
	{
	public:
		explicit InvalidOperationException(const char* msg)
			: std::runtime_error(msg) {};

		explicit InvalidOperationException(const std::string& msg)
			: std::runtime_error(msg) {};
	};
}
