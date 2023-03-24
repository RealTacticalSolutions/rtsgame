#pragma once



class window;

class application {
private:
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;

	const glm::vec3 DEFAULT_CAM_POS = glm::vec3(1.0f, 0.0f, 2.0f);
	const glm::vec3 DEFAULT_CAM_LOOK_POS = glm::vec3(0.0f, 0.0f, 0.0f);
	const glm::vec3 DEFAULT_CAM_UP_POS = glm::vec3(0.0f, 0.0f, 1.0f);
	const float DEFAULT_FOV = glm::radians(45.0f);
	const float DEFAULT_NEAR_CLIPPING_PLANE = 0.1f;
	const float DEFAULT_FAR_CLIPPING_PLANE = 10.0f;

	int indexOffset = 0;
	
	std::unique_ptr<renderer> vulkanrenderer;
	std::unique_ptr<window> windowObject;

	Scene scene;
	Camera camera;
	std::vector<GameObject> gameObjects;
	std::vector<messageObject> message;


	void updateColor(int index, glm::vec3 color);
	void updateColorAddition(int index, glm::vec3 color);
	bool approxEqual(glm::vec3 a, glm::vec3 b, float epsilon);
	void updateWayPoints();
public:
	
	application() : camera(DEFAULT_CAM_POS, DEFAULT_CAM_LOOK_POS, DEFAULT_CAM_UP_POS, DEFAULT_FOV, DEFAULT_NEAR_CLIPPING_PLANE, DEFAULT_FAR_CLIPPING_PLANE), scene()
	{
	};
	~application()
	{
	};

	
	void constructGameobjects();
	void initWindow();
	void start();
	void mainLoop();
	void drawFrame();
	void cleanup();
	void updateTest();
};