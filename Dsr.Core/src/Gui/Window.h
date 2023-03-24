#pragma once

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Events/EventHandler.h"
#include "Events/WindowEvents.h"
#include "LogManager.h"
#include "Viewport.h"
#include "WindowData.h"
#include "WindowInitStatus.h"

namespace dsr
{
	namespace gui
	{
		struct WindowProps
		{
			std::string Title;
			int Width, Height;

			WindowProps()
			{
				Title = "Window";
				Width = 1024;
				Height = 768;
			}
		};

		class Window
		{
		public:
			dsr::events::EventHandler<dsr::events::EventReceiver, dsr::events::WindowResizeEvent> ResizeEvent;
			dsr::events::EventHandler<dsr::events::EventReceiver, dsr::events::Event> UpdateEvent;
			dsr::events::EventHandler<dsr::events::EventReceiver, dsr::events::WindowUpdateEvent> WindowUpdateEvent;

			WindowInitStatus Init();
			void Show();

			Window(const WindowProps& props);

			Window(const Window& other) = delete;
			Window& operator=(const Window& other) = delete;
			~Window();
		private:
			class WindowMangager : public dsr::events::EventReceiver
			{
			public:
				WindowMangager(std::shared_ptr<WindowData> data)
					: m_data(data), m_logger(dsr::LogManager::GetLogger("dsr::Window::WindowManager"))
				{}

				void OnResize(dsr::events::WindowResizeEvent& resizeEvent);
			private:
				std::shared_ptr<WindowData> m_data;
				std::shared_ptr<spdlog::logger> m_logger;
			};

			void SetupResizeEventHandler();
			/*void SetupWindowCloseEventHandler();*/

			GLFWwindow* m_window = nullptr;

			std::shared_ptr<WindowData> m_data;
			std::shared_ptr<WindowMangager> m_windowManager;
			std::shared_ptr<spdlog::logger> m_logger;
		};
	}
}
