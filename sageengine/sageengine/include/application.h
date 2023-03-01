#pragma once

class window;
class renderer;

class application {
private:
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;
	
	std::unique_ptr<renderer> vulkanrenderer;
	std::unique_ptr<window> windowObject;

	Camera camera;
	std::vector<GameObject> gameObjects;
	std::vector<messageObject> message;


	void updateColor(int index, glm::vec3 color);
	void updateColorAddition(int index, glm::vec3 color);
public:
	// TODO:: camera doenst draw object when it looks at direct 0.0f ,0.0f,0.0f, when its at 0.0f,0.0f,4.0f
	application() : camera(glm::vec3(0.0f, 0.001f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::radians(45.0f), 0.1f, 10.0f) 
	{
	};
	~application()
	{
	};

	
	std::vector<GameObject> constructGameobjects();
	void initWindow();
	void mainLoop();
	void drawFrame();
	void cleanup();
};