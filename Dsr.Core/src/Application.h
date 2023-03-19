#pragma once

#include <memory>
#include <functional>

#include "Gui/Window.h"

namespace dsr
{
	class Application
	{
	public:
		Application();



		virtual ~Application();
	private:
		std::shared_ptr<dsr::gui::Window> m_window;
	};
}
