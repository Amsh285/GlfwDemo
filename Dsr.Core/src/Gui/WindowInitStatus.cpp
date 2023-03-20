
#include "dsrpch.h"
#include "WindowInitStatus.h"

namespace dsr
{
	namespace gui
	{
		WindowInitStatus WindowInitStatus::Success()
		{
			return WindowInitStatus("Window initialized.", WindowInitResult::Success);
		}

		WindowInitStatus WindowInitStatus::GlfwWindowCreationFailed()
		{
			return WindowInitStatus("Failed to create GLFW window.", WindowInitResult::GlfwWindowCreationFailed);
		}

		WindowInitStatus WindowInitStatus::GladInitializationFailed()
		{
			return WindowInitStatus("Failed to initialize GLAD.", WindowInitResult::GladInitializationFailed);
		}
	}
}
