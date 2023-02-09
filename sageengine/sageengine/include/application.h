#pragma once

class window;

class application {
private:
	int WIDTH = 800;
	int HEIGHT = 600;
	std::unique_ptr<window> program;

public:
	application()
	{
	};
	~application()
	{
	};

	
	void run();
};