#pragma once

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowInitStatus.h"

namespace dsr
{
	namespace gui
	{
		struct Viewport
		{
			int X, Y;
			int Width, Height;
		};

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

		class Window
		{
		public:
			WindowInitStatus Init();
			void Show();
			void OnEvent();

			Window(const WindowData& data)
				: m_data(data) {}

			
			Window(const Window& other) = delete;
			Window& operator=(const Window& other) = delete;
			~Window();
		private:
			WindowData m_data;
			GLFWwindow* m_window = nullptr;
		};
	}
}
