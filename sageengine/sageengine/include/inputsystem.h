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

	/*
	*	@brief a function that returns true if a given key is pressed
	* 
	*	@param key the key to check for
	*	@returns returns if key is pressed or not
	*/
	bool keyPressed(int key);

	/*
	*	@brief a function that returns true if a given key is released
	*
	*	@param key the key to check for
	*	@returns returns if key is released this frame
	*/
	bool keyUp(int key);

	/*
	*	@brief a function that returns true if a given key is pressed first this frame
	*
	*	@param key the key to check for
	*	@returns returns if key is pressed first this frame
	*/
	bool keyDown(int key);
	

	/** updates the keystate for each key every frame */
	void updateInput();


	bool Input::mouseButtonPressed(int button);

	/*
	*	@brief a function that gets the cursor position in relation to the window
	*
	*	@returns returns a vector2 that holds the x and y position of the cursor in pixels from away from the window origin
	*/
	glm::vec2 getCursorPos();
};
