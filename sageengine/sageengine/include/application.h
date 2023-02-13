#pragma once

class window;
class renderer;

class application {
private:
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;
	
	std::unique_ptr<renderer> vulkanrenderer;
	std::unique_ptr<window> windowObject;

public:
	application()
	{
	};
	~application()
	{
	};

	
	
	void initWindow();
	void mainLoop();
	void cleanup();
};