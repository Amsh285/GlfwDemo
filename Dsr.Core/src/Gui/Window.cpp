#include "Window.h"

namespace dsr
{
	namespace gui
	{
		WindowInitStatus Window::Init()
		{
			m_window = glfwCreateWindow(m_data->Width, m_data->Height, m_data->Title.c_str(), NULL, NULL);

			if (m_window == nullptr)
				return WindowInitStatus::GlfwWindowCreationFailed();

			glfwMakeContextCurrent(m_window);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
				return WindowInitStatus::GladInitializationFailed();

			glViewport(m_data->View.X, m_data->View.Height, m_data->View.Width, m_data->View.Height);

			glfwSetWindowUserPointer(m_window, this);
			SetupResizeEventHandler();
			SetupWindowCloseEventHandler();

			return WindowInitStatus::Success();
		}

		void Window::Show()
		{
			while (!glfwWindowShouldClose(m_window))
			{
				glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);
				//render here


				glfwSwapBuffers(m_window);
				glfwPollEvents();
			}
		}

		Window::Window(const WindowProps& props)
		{
			m_data = std::make_shared<WindowData>();
			m_data->Title = props.Title;
			m_data->Width = props.Width;
			m_data->Height = props.Height;
			m_data->View.X = m_data->View.Y = 0;
			m_data->View.Width = props.Width;
			m_data->View.Height = props.Height;
			m_data->View.Width_f = props.Width;
			m_data->View.Height_f = props.Height;

			m_windowManager = std::make_shared<WindowMangager>(m_data);
			m_logger = dsr::LogManager::GetLogger("dsr::Window");
		}

		Window::~Window()
		{
			glfwDestroyWindow(m_window);
		}

		void Window::SetupResizeEventHandler()
		{
			glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int newWidth, int newHeight)
				{
					Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
					dsr::events::WindowResizeEvent event(newWidth, newHeight);
					instance->m_resizeEvent(event);
				});

			m_resizeEvent.Hook(m_windowManager, &WindowMangager::OnResize);
		}

		void Window::SetupWindowCloseEventHandler()
		{
			/*glfwSetWindowCloseCallback*/
		}

		void Window::WindowMangager::OnResize(dsr::events::WindowResizeEvent& resizeEvent)
		{
			m_logger->info("OnResize: new Size ({0}, {1})", resizeEvent.GetNewWidth(), resizeEvent.GetNewHeight());

			float w_factor = (float)resizeEvent.GetNewWidth() / (float)m_data->Width;
			float h_factor = (float)resizeEvent.GetNewHeight() / (float)m_data->Height;

			m_logger->info("OnResize: factors ({0}, {1})", w_factor, h_factor);
			m_logger->info("OnResize: m_data old Size: ({0}, {1})", m_data->Width, m_data->Height);

			m_data->Width = resizeEvent.GetNewWidth();
			m_data->Height = resizeEvent.GetNewHeight();
			m_data->View.Width_f *= w_factor;
			m_data->View.Height_f *= h_factor;
			m_data->View.Width = m_data->View.Width_f;
			m_data->View.Height = m_data->View.Height_f;

			glViewport(m_data->View.X, m_data->View.Height, m_data->View.Width, m_data->View.Height);
			m_logger->info("OnResize: m_data new Size: ({0}, {1})", m_data->Width, m_data->Height);
			m_logger->info("OnResize: m_data new Viewport: ({0}, {1})", m_data->View.Width, m_data->View.Height);
			m_logger->info("OnResize: m_data new Viewport_f: ({0}, {1})", m_data->View.Width_f, m_data->View.Height_f);
		}
	}
}
