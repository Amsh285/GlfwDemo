
#include "dsrpch.h"
#include "WindowApplication.h"

namespace dsr
{
	ApplicationExitCodes WindowApplication::Run()
	{
		dsr::GlfwInitialize init;

		if (!init.GetResult())
			return ApplicationExitCodes("Failed to initialize GLFW.", -100);

		
		dsr::gui::WindowInitStatus windowInitStatus = m_window->Init();

		if (windowInitStatus.GetResult() != dsr::gui::WindowInitResult::Success)
			return ApplicationExitCodes(windowInitStatus.GetDescription(), static_cast<int>(windowInitStatus.GetResult()));

		dsr::ApplicationExitCodes setupExitCode = Setup();

		if (setupExitCode.Code != dsr::ApplicationExitCodes::SuccessExitCode)
			return setupExitCode;

		m_window->HookWindowUpdateEvent(m_renderer, static_cast<dsr::gui::Window::WindowUpdateEventCallback>(&dsr::render::Renderer::Update));
		m_window->Show();

		return ApplicationExitCodes::Success();
	}
}
