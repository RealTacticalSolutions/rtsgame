#include "pch.h"
#include "application.h"



void application::mainLoop()
{
	initWindow();
	while (!program->shouldClose())
	{
		glfwPollEvents();
	}
}

void application::initWindow()
{
	program = std::make_unique<window>(WIDTH, HEIGHT);

}

void application::cleanup()
{
}