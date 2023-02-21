
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

unsigned int register_triangle()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, vertices, GL_STATIC_DRAW);

	//ka mal schaun
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	return vbo;
}

unsigned int register_vertex_shader()
{
	const char* src ="#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"\n"
		"void main()\n"
		"{\n"
		" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	unsigned int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &src, NULL);
	glCompileShader(vertex_shader);

	return vertex_shader;
}

unsigned int register_fragment_shader()
{
	const char* src = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &src, NULL);
	glCompileShader(fragment_shader);

	return fragment_shader;
}

unsigned int register_shader_program(const unsigned int& vertex_shader_id, const unsigned int& fragment_shader_id)
{
	unsigned int shader_program;
	shader_program = glCreateProgram();

	glAttachShader(shader_program, vertex_shader_id);
	glAttachShader(shader_program, fragment_shader_id);
	glLinkProgram(shader_program);

	return shader_program;
}

bool check_shader(unsigned shader_id)
{
	int success;
	char info_log[512];
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader_id, 512, NULL, info_log);
		std::cout << "Shader compilation failed:" << std::endl << info_log << std::endl;
		return false;
	}

	return true;
}

bool check_shader_program(unsigned shader_program_id)
{
	int success;
	char info_log[512];
	glGetShaderiv(shader_program_id, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader_program_id, 512, NULL, info_log);
		std::cout << "linking failed:" << std::endl << info_log << std::endl;
		return false;
	}

	return true;
}

int main()
{
	// Warum geht das nicht hier?
	/*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return EXIT_FAILURE;
	}

	// Fehlt das?
	glfwMakeContextCurrent(window);
	*/

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

	unsigned int vao_id;
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	unsigned int vbo_id = register_triangle();

	unsigned int vertex_shader_id = register_vertex_shader();
	unsigned int fragment_shader_id = register_fragment_shader();

	if (!check_shader(vertex_shader_id))
		return EXIT_FAILURE;

	if (!check_shader(fragment_shader_id))
		return EXIT_FAILURE;

	unsigned shader_program_id = register_shader_program(vertex_shader_id, fragment_shader_id);

	if (!check_shader_program(shader_program_id))
		return EXIT_FAILURE;

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		process_input(window);

		//render here
		glUseProgram(shader_program_id);
		glBindVertexArray(vao_id);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}
