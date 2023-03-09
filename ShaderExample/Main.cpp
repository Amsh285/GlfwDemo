
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

std::shared_ptr<dsr::VaoAggregate> LoadTriangle()
{
	std::shared_ptr<spdlog::logger> logger = dsr::loggerfactory::CreateLogger("Load Geometry");

	try
	{
		std::vector<float> buffer = {
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};

		std::vector<unsigned int> indices = {
			0,1,2
		};

		dsr::VertexAttributeContainer attributes;
		attributes.Append(3);
		attributes.Append(4);

		// notice: add vertexcount on higher level objects for simplified rendering
		// e.g.: GameObject/Geometry { Vao, VertexCount, Transforms }
		return std::make_shared<dsr::VaoAggregate>(dsr::VaoAggregate::Build(buffer, indices, attributes));
	}
	catch (const std::exception& ex)
	{
		logger->warn("Error loading geometries: {0}", ex.what());
		return std::shared_ptr<dsr::VaoAggregate>();
	}
}

std::shared_ptr<dsr::ShaderProgram> LoadShaders()
{
	std::shared_ptr<spdlog::logger> logger = dsr::loggerfactory::CreateLogger("Shaderfac");

	try
	{
		std::shared_ptr<dsr::Shader> vertexShader = dsr::Shader::Load("shaders/vertexshader.shader", dsr::ShaderType::Vertex);
		vertexShader->Compile();
		dsr::ShaderCompileStatus vertexShaderCompileState = vertexShader->GetCompileStatus();

		logger->info("Vertexshader Status: {0} Message: {1}", vertexShaderCompileState.Success, vertexShaderCompileState.InfoLog);

		std::shared_ptr<dsr::Shader> fragmentShader = dsr::Shader::Load("shaders/fragmentshader.shader", dsr::ShaderType::Fragment);
		fragmentShader->Compile();
		dsr::ShaderCompileStatus fragmentShaderCompileState = fragmentShader->GetCompileStatus();

		logger->info("Fragmentshader Status: {0} Message: {1}", fragmentShaderCompileState.Success, fragmentShaderCompileState.InfoLog);

		std::shared_ptr<dsr::ShaderProgram> shaderProgram = dsr::ShaderProgram::GenerateGL();
		shaderProgram->Attach(vertexShader);
		shaderProgram->Attach(fragmentShader);
		shaderProgram->Link();

		dsr::ShaderLinkStatus linkStatus = shaderProgram->GetLinkStatus();
		logger->info("Shaderprogram Status: {0} Message: {1}", linkStatus.Success, linkStatus.InfoLog);

		return shaderProgram;
	}
	catch (const std::exception& ex)
	{
		logger->warn("Error loading Shaders: {0}", ex.what());
		return std::shared_ptr<dsr::ShaderProgram>();
	}
}

int main()
{
	if (!glfwInit())
	{
		std::cout << "Error initializing OpenGL." << std::endl;
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Ich will heim.", NULL, NULL);

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

	std::shared_ptr<dsr::ShaderProgram> shaderProgram = LoadShaders();
	std::shared_ptr<dsr::VaoAggregate> vao = LoadTriangle();

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		process_input(window);
		//render here

		if (shaderProgram)
			shaderProgram->Use();

		if (vao)
		{
			vao->Bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
			vao->Unbind();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}
