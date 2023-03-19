#pragma once

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Events/EventHandler.h"
#include "Events/WindowEvents.h"
#include "LogManager.h"
#include "WindowInitStatus.h"

namespace dsr
{
	namespace gui
	{
		struct Viewport
		{
			int X, Y;
			int Width, Height;
			float Width_f, Height_f;
		};

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
			WindowInitStatus Init();
			void Show();

			Window(const WindowProps& props);

			Window(const Window& other) = delete;
			Window& operator=(const Window& other) = delete;
			~Window();
		private:
			struct WindowData
			{
				std::string Title;
				int Width, Height;
				Viewport View;

				WindowData()
				{
					Title = "Window";
					Width = 1024;
					Height = 768;

					View.X = View.Y = 0;
					View.Width = 1024;
					View.Height = 768;
				}
			};

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
			void SetupWindowCloseEventHandler();

			GLFWwindow* m_window = nullptr;

			dsr::events::EventHandler<dsr::events::EventReceiver, dsr::events::WindowResizeEvent> m_resizeEvent;

			std::shared_ptr<WindowData> m_data;
			std::shared_ptr<WindowMangager> m_windowManager;
			std::shared_ptr<spdlog::logger> m_logger;
		};
	}
}
