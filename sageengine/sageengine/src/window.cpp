#include "pch.h"
#include "window.h"

void window::initWindow(int width, int height)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	mainWindow = glfwCreateWindow(width, height, "Vulkan window", nullptr, nullptr);

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
