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
			using EventReceiver = std::shared_ptr<dsr::events::EventReceiver>;
			using EventCallback = dsr::events::EventHandler<dsr::events::EventReceiver, dsr::events::Event>::EventDelegate;
			using WindowUpdateEventCallback = dsr::events::EventHandler<dsr::events::EventReceiver, dsr::events::WindowUpdateEvent>::EventDelegate;

			void HookUpdateEvent(const EventReceiver& receiver, EventCallback callback);
			void UnhookUpdateEvent(const EventReceiver& receiver);

			void HookWindowUpdateEvent(const EventReceiver& receiver, WindowUpdateEventCallback callback);
			void UnhookWindowUpdateEvent(const EventReceiver& receiver);

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

			dsr::events::EventHandler<dsr::events::EventReceiver, dsr::events::Event> m_updateEvent;
			dsr::events::EventHandler<dsr::events::EventReceiver, dsr::events::WindowUpdateEvent> m_windowUpdateEvent;
			dsr::events::EventHandler<dsr::events::EventReceiver, dsr::events::WindowResizeEvent> m_resizeEvent;

			std::shared_ptr<WindowData> m_data;
			std::shared_ptr<WindowMangager> m_windowManager;
			std::shared_ptr<spdlog::logger> m_logger;
		};
	}
}
