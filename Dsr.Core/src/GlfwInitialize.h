#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace dsr
{
	class GlfwInitialize
	{
	public:
		inline const int& GetResult() const { return m_result; }

		GlfwInitialize()
		{
			m_result = glfwInit();
		}

		GlfwInitialize(const GlfwInitialize& other) = delete;
		GlfwInitialize& operator=(const GlfwInitialize& other) = delete;
		~GlfwInitialize() { glfwTerminate(); }
	private:
		int m_result;
	};
}
