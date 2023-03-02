#include <iostream>
#include <vector>
#include "DsrCore.h"

#include "Shader.h"
#include "ShaderProgram.h"
#include "SpdLoggerFactory.h"

#include "VaoAggregate.h"

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

std::vector<dsr::VaoAggregate> register_triangles()
{
	std::vector<dsr::VaoAggregate> vaos;

	std::vector<unsigned int> indices = {
		0, 1, 2
	};

	std::vector<float> first_triangle = {
		0.5f, 0.5f, 0.0f,
		0.75f, 0.0f, 0.0f,
		0.25f, 0.0f, 0.0f,
	};

	dsr::VertexAttributeContainer attributes;
	attributes.Append(3);

	dsr::VaoAggregate vao1 = dsr::VaoAggregate::Build(first_triangle, indices, attributes);
	vaos.push_back(vao1);

	std::vector<float> second_triangle = {
		-0.5f, 0.5f, 0.0f,
		-0.25f, 0.0f, 0.0f,
		-0.75f, 0.0f, 0.0f
	};

	dsr::VaoAggregate vao2 = dsr::VaoAggregate::Build(second_triangle, indices, attributes);
	vaos.push_back(vao2);

	return vaos;
}

std::vector<std::shared_ptr<dsr::ShaderProgram>> LoadShaders(const std::shared_ptr<spdlog::logger>& logger)
{
	std::vector<std::shared_ptr<dsr::ShaderProgram>> programs;

	std::shared_ptr<dsr::Shader> vertexShader = dsr::Shader::Load("shaders/vertexshader.shader", dsr::ShaderType::Vertex);
	vertexShader->Compile();
	dsr::ShaderCompileStatus vertexShaderStatus = vertexShader->GetCompileStatus();

	if (!vertexShaderStatus.Success)
	{
		logger->warn("Error compiling VertexShader: {0}", vertexShaderStatus.InfoLog);
		return programs;
	}

	std::shared_ptr<dsr::Shader> fragmentShaderRed = dsr::Shader::Load("shaders/fragmentshader_red.shader", dsr::ShaderType::Fragment);
	fragmentShaderRed->Compile();
	dsr::ShaderCompileStatus fragmentShaderRedStatus = fragmentShaderRed->GetCompileStatus();

	if (!fragmentShaderRedStatus.Success)
	{
		logger->warn("Error compiling FragmentShaderRed: {0}", fragmentShaderRedStatus.InfoLog);
		return programs;
	}

	std::shared_ptr<dsr::ShaderProgram> program1 = dsr::ShaderProgram::GenerateGL();
	program1->Attach(vertexShader);
	program1->Attach(fragmentShaderRed);
	program1->Link();

	dsr::ShaderLinkStatus linkStatus1 = program1->GetLinkStatus();

	if(!linkStatus1.Success)
	{ 
		logger->warn("Error linking ShaderProgram Nr.1: {0}", linkStatus1.InfoLog);
		return programs;
	}

	programs.push_back(program1);

	std::shared_ptr<dsr::Shader> fragmentShaderGreen = dsr::Shader::Load("shaders/fragmentshader_green.shader", dsr::ShaderType::Fragment);
	fragmentShaderGreen->Compile();
	dsr::ShaderCompileStatus fragmentShaderGreenStatus = fragmentShaderRed->GetCompileStatus();

	if (!fragmentShaderGreenStatus.Success)
	{
		logger->warn("Error compiling FragmentShaderGreen: {0}", fragmentShaderGreenStatus.InfoLog);
		return programs;
	}

	std::shared_ptr<dsr::ShaderProgram> program2 = dsr::ShaderProgram::GenerateGL();
	program2->Attach(vertexShader);
	program2->Attach(fragmentShaderGreen);
	program2->Link();

	dsr::ShaderLinkStatus linkStatus2 = program2->GetLinkStatus();

	if (!linkStatus2.Success)
	{
		logger->warn("Error linking ShaderProgram Nr.2: {0}", linkStatus1.InfoLog);
		return programs;
	}

	programs.push_back(program2);
	return programs;
}

int main()
{
	const std::shared_ptr<spdlog::logger> logger = dsr::loggerfactory::CreateLogger("ex.5.8.3");

	if (!glfwInit())
	{
		std::cout << "Error initializing OpenGL." << std::endl;
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "yay Triangle", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return EXIT_FAILURE;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	std::vector<dsr::VaoAggregate> vaos = register_triangles();
	std::vector<std::shared_ptr<dsr::ShaderProgram>> shaderPrograms = LoadShaders(logger);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		process_input(window);

		//render here

		for (size_t i = 0; i < vaos.size(); i++)
		{
			auto currentVao = vaos[i];

			if (i < shaderPrograms.size())
				shaderPrograms[i]->Use();

			currentVao.Bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
			currentVao.Unbind();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}
