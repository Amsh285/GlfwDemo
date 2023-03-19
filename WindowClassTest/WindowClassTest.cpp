

#include <iostream>

#include "GlfwInitialize.h"

#include "ShaderProgram.h"
#include "SpdLoggerFactory.h"
#include "VaoAggregate.h"
#include "Gui/Window.h"

int main()
{
	std::shared_ptr<spdlog::logger> logger = dsr::loggerfactory::CreateLogger("main");

	dsr::GlfwInitialize init;

	if (!init.GetResult())
	{
		logger->error("Failed to initialize GLFW. Shutting down.");
		return EXIT_FAILURE;
	}
		
	dsr::gui::Window* window = new dsr::gui::Window(dsr::gui::WindowProps());
	window->Init();
	window->Show();

	delete window;
	return EXIT_SUCCESS;
}