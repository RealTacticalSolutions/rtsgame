#include "pch.h"
#include "application.h"



void application::mainLoop()
{
	std::unique_ptr<renderer> vulkanrenderer = std::make_unique<renderer>();

	initWindow();
	vulkanrenderer->initVulkan(std::move(windowObject));
	while (!windowObject->shouldClose())
	{
		glfwPollEvents();
	}
}

void application::initWindow()
{
	windowObject = std::make_unique<window>(WIDTH, HEIGHT);

}

void application::cleanup()
{
}