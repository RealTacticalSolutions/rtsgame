#include "pch.h"
#include "window.h"

static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	// TODO: maybe use this to also cast pointer to the renderer class instead of passing it through functions?
	auto app = reinterpret_cast<renderer*>(glfwGetWindowUserPointer(window));
	app->framebufferResized = true;
}

void window::initWindow(int width, int height)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	mainWindow = glfwCreateWindow(width, height, "Vulkan window", nullptr, nullptr);
	glfwSetWindowUserPointer(mainWindow, m_vulkanrenderer);
	glfwSetFramebufferSizeCallback(mainWindow, framebufferResizeCallback);
 
}

void window::cleanupGLFW()
{
	glfwDestroyWindow(mainWindow);

	glfwTerminate();
	std::cout << "cleanupGLFW" << std::endl;
}

GLFWwindow* window::getWindow()
{ 
	return mainWindow;
}

