#include "pch.h"
#include "application.h"


void application::mainLoop()
{
	while (!windowObject->shouldClose())
	{
		glfwPollEvents();
		drawFrame();
	}
	vkDeviceWaitIdle(vulkanrenderer->getDevice());
}

void application::drawFrame()
{
	vulkanrenderer->renderer::drawFrame(windowObject->getWindow());
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