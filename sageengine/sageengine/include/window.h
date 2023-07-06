#pragma once

class renderer;

class window {

private:
	const int WIDTH;
	const int HEIGHT;

	GLFWwindow* mainWindow;
	renderer* m_vulkanrenderer;

	/*
	 * @brief Initializes the GLFW window with a specified width and height.
	 *
	 * @param width  The width of the window.
	 * @param height The height of the window.
	 */
	void initWindow(int width, int height);

	/*
	 * @brief Cleans up the GLFW resources.
	 */
	void cleanupGLFW();

public:
	window(int width, int height, renderer* vulkanrenderer) : WIDTH(width), HEIGHT(height), m_vulkanrenderer(vulkanrenderer)
	{
		initWindow(width, height);
	};
	~window() 
	{
		cleanupGLFW();
	};

	/*
	 * @brief Checks if the GLFW window should close.
	 *
	 * @return True if the window should close, false otherwise.
	 */
	bool shouldClose() { return glfwWindowShouldClose(mainWindow); }

	/*
	 * @brief Retrieves the GLFW window.
	 *
	 * @return The GLFW window.
	 */
	GLFWwindow* getWindow();

};