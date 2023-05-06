#include "pch.h"

enum KeyState
{
	NOT_PRESSED,
	PRESSED,
	DOWN,
	RELEASED
};

static std::map<int, int> keyMap = {
	{GLFW_KEY_SPACE, 0},
	{GLFW_KEY_A, 0},
	{GLFW_KEY_D, 0},
	{GLFW_KEY_S, 0},
	{GLFW_KEY_W, 0},
	{GLFW_KEY_E, 0},
	{GLFW_MOUSE_BUTTON_LEFT, 0},
	{GLFW_MOUSE_BUTTON_RIGHT, 0},
};

bool Input::keyPressed(int key)
{
	int state = glfwGetKey(window, key);
	if (state == GLFW_PRESS) {
		return true;
	}
}

bool Input::mouseButtonPressed(int button)
{
	int state = glfwGetMouseButton(window, button);
	if (state == GLFW_PRESS) {
		return true;
	}
	return false;
}

//TODO MAYBE GIVE KEYUP FUNCTION IMPLEMENTATION
bool Input::keyUp(int key)
{
    return false;
}

bool Input::keyDown(int key)
{
	if (keyMap[key] == 2) {
		return true;
	}
	return false;
}

void Input::initCallback()
{
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS) {
			if (keyMap[key] == DOWN) {
				keyMap[key] = PRESSED;
			}
			else {
				keyMap[key] = DOWN;
			}
		}
		else if (action == GLFW_RELEASE) {
			keyMap[key] = RELEASED;
		}
		else {
			keyMap[key] = NOT_PRESSED;
		}
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int key, int action, int mods) {
		if (action == GLFW_PRESS) {
			if (keyMap[key] == DOWN) {
				keyMap[key] = PRESSED;
			}
			else {
				keyMap[key] = DOWN;
			}
		}
		else if (action == GLFW_RELEASE) {
			keyMap[key] = RELEASED;
		}
		else {
			keyMap[key] = NOT_PRESSED;
		}
		});
}



void Input::updateInput() {
	for (const auto &pair : keyMap) {
		if (pair.second == 2) {
			keyMap[pair.first] = 1;
		}
		else {
			keyMap[pair.first] = 0;
		}
	}
};

glm::vec2 Input::getCursorPos()
{
	double xPos;
	double yPos;

	glfwGetCursorPos(window, &xPos, &yPos);
	return glm::vec2(xPos, yPos);
}


