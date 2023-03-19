#pragma once

#include <string>

namespace dsr
{
	namespace gui
	{
		enum class WindowInitResult
		{
			Success = 0,
			GlfwWindowCreationFailed = 100,
			GladInitializationFailed = 101
		};

		class WindowInitStatus
		{
		public:
			static WindowInitStatus Success();
			static WindowInitStatus GlfwWindowCreationFailed();
			static WindowInitStatus GladInitializationFailed();

			const std::string& GetDescription() const { return m_description; };
			const WindowInitResult& GetResult() const { return m_result; };

			WindowInitStatus(const std::string& description, const WindowInitResult& result)
				: m_description(description), m_result(result) {};
		private:
			std::string m_description;
			WindowInitResult m_result;
		};
	}
}
