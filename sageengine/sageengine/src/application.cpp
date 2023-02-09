#include "pch.h"
#include "application.h"



void application::run()
{
	program = std::make_unique<window>(WIDTH, HEIGHT);

	while (!program->shouldClose())
	{
		glfwPollEvents();
	}
}
