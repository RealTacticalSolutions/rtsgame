#pragma once


class window {

private:
	const int WIDTH;
	const int HEIGHT;

	GLFWwindow* mainWindow;

	void initWindow(int width, int height);

	void cleanup();

public:
	window(int width, int height) : WIDTH(width), HEIGHT(height)
	{
		initWindow(width, height);
	};
	~window() 
	{
		cleanup();
	};

	bool shouldClose() { return glfwWindowShouldClose(mainWindow); };

	
};