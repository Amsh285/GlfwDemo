#include "Window.h"

namespace dsr
{
	namespace gui
	{
		void FrameBufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight)
		{
			Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));

			//Todo: bau den shit richtig rein
			/*glViewport()*/

			instance->OnEvent();
		}

		WindowInitStatus Window::Init()
		{
			m_window = glfwCreateWindow(m_data.Width, m_data.Height, m_data.Title.c_str(), NULL, NULL);

			if (m_window == nullptr)
				return WindowInitStatus::GlfwWindowCreationFailed();

			glfwMakeContextCurrent(m_window);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
				return WindowInitStatus::GladInitializationFailed();

			glViewport(m_data.View.X, m_data.View.Height, m_data.View.Width, m_data.View.Height);

			glfwSetWindowUserPointer(m_window, this);
			glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallback);

			return WindowInitStatus::Success();
		}

		void Window::Show()
		{
			while (!glfwWindowShouldClose(m_window))
			{
				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);
				//render here


				glfwSwapBuffers(m_window);
				glfwPollEvents();
			}
		}

		void Window::OnEvent()
		{
		}

		Window::~Window()
		{
			glfwDestroyWindow(m_window);
		}
	}
}
