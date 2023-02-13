#include "pch.h"
#include "application.h"



void application::mainLoop()
{
	while (!windowObject->shouldClose())
	{
		glfwPollEvents();
	}
}

void application::initWindow()
{
	vulkanrenderer = std::make_unique<renderer>();
	windowObject = std::make_unique<window>(WIDTH, HEIGHT);
	
	vulkanrenderer->initVulkan(std::move(windowObject));

}

void application::cleanup()
{
}