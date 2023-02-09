#pragma once

class window;

class program {
private:
	int WIDTH = 800;
	int HEIGHT = 600;
	std::unique_ptr<window> programWindow;

public:
	program()
	{
	};
	~program()
	{
	};

	
	void run();
};