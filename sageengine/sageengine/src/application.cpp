#include "pch.h"
#include "application.h"



void application::mainLoop()
{
	std::unique_ptr<renderer> vulkanrenderer = std::make_unique<renderer>();

	initWindow();
	vulkanrenderer->initVulkan();
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