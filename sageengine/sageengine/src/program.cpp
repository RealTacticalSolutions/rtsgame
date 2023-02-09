#include "pch.h"
#include "program.h"



void program::run()
{
	programWindow = std::make_unique<window>(WIDTH, HEIGHT);

	while (!programWindow->shouldClose())
	{
		glfwPollEvents();
	}
}
