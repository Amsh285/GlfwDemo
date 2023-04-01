#pragma once

#include "Application.h"
#include "GlfwInitialize.h"
#include "Render/RenderContextRegister.h"
#include "Render/Renderer.h"
#include "Gui/Window.h"

namespace dsr
{
	class WindowApplication : public Application
	{
	public:
		WindowApplication() :
			m_renderContextRegister(std::make_shared<render::RenderContextRegister>()),
			m_renderer(std::make_shared<render::Renderer>(m_renderContextRegister)),
			m_window(std::make_shared<gui::Window>(gui::WindowProps()))
		{}

		ApplicationExitCodes Run() override;
		virtual ~WindowApplication() {}
	protected:
		virtual ApplicationExitCodes Setup() = 0;

		std::shared_ptr<render::RenderContextRegister> m_renderContextRegister;
		std::shared_ptr<render::Renderer> m_renderer;
		std::shared_ptr<gui::Window> m_window;
	};
}
