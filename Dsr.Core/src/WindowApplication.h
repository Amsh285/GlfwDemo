#pragma once

#include "Application.h"
#include "GlfwInitialize.h"
#include "Render/Renderer.h"
#include "Gui/Window.h"

namespace dsr
{
	class WindowApplication : public Application
	{
	public:
		WindowApplication() : 
			m_renderer(std::make_shared<dsr::render::Renderer>()),
			m_window(std::make_shared<dsr::gui::Window>(dsr::gui::WindowProps()))
		{}

		ApplicationExitCodes Run() override;
		virtual ~WindowApplication() {}
	protected:
		virtual ApplicationExitCodes Setup() = 0;

		std::shared_ptr<dsr::render::Renderer> m_renderer;
		std::shared_ptr<dsr::gui::Window> m_window;
	};
}
