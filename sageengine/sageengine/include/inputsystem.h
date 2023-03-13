#pragma once

static class Input {

private:
	GLFWwindow* window;
	std::vector<int> keysPressed;
	std::vector<int> keysDown;

	void initCallback();

public:
	Input(GLFWwindow* window) : window(window) {
		initCallback();
	};

	bool keyPressed(int key);
	bool keyUp(int key);
	bool keyDown(int key);
	
	void updateInput();

	glm::vec2 getCursorPos();
};
