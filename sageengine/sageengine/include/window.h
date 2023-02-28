#pragma once


class window {

private:
	const int WIDTH;
	const int HEIGHT;

	GLFWwindow* mainWindow;
	renderer* m_vulkanrenderer;

	void initWindow(int width, int height);

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

	bool shouldClose() { return glfwWindowShouldClose(mainWindow); };

	GLFWwindow* getWindow();

};