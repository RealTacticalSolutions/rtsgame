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
	std::vector<messageObject> message;

	std::vector<WayPoints> paths;
	glm::vec3 spawnpoint = glm::vec3(0.34f,-1.0f,1.0f);

	std::vector<TrafficLight> lights;

	std::vector<glm::vec3> lightspos =
	{ 
	glm::vec3(0.52f,0.18f,1.0f),//1.1
	glm::vec3(0.52f,0.0f,1.0f),//2.1
	glm::vec3(0.52f,0.35f,1.0f),//42.0 
	glm::vec3(0.10f,0.50f,1.0f),//12.1 
	glm::vec3(-0.18f,0.50f,1.0f),//11.1
	glm::vec3(-0.38f,0.50f,1.0f),//10.1 
	glm::vec3(-0.50f,0.0f,1.0f),//9.1 
	glm::vec3(-0.50f,-0.20f,1.0f),//8.1 
	glm::vec3(-0.50f,-0.40f,1.0f),//7.1 
	glm::vec3(0.16f,-0.54f,1.0f),//6.1 
	glm::vec3(0.34f,-0.54f,1.0f),//5.1 
	glm::vec3(-1.4f,0.8f,1.0f),//35.1
	glm::vec3(-1.4f,0.6f,1.0f),//35.2
	glm::vec3(-1.4f,0.4f,1.0f),//36.1
	glm::vec3(-1.4f,0.2f,1.0f),//36.2
	glm::vec3(-1.4f,0.0f,1.0f),//37.1
	glm::vec3(-1.4f,-0.2f,1.0f),//37.2
	glm::vec3(-1.4f,-0.4f,1.0f),//38.1
	glm::vec3(-1.4f,-0.6f,1.0f),//38.2
	glm::vec3(-1.4f,-0.8f,1.0f),//31.1
	glm::vec3(-1.2f,0.8f,1.0f),//31.2
	glm::vec3(-1.2f,0.6f,1.0f),//32.1
	glm::vec3(-1.2f,0.4f,1.0f),//32.2
	glm::vec3(-1.2f,0.2f,1.0f),//86.1
	glm::vec3(-1.2f,-0.0f,1.0f),//26.1
	glm::vec3(-1.2f,-0.2f,1.0f),//88.1
	glm::vec3(-1.2f,-0.4f,1.0f),//28.1
	glm::vec3(-1.2f,-0.6f,1.0f)//22.0

	};

	void updateColor(int index, glm::vec3 color);
	void updateColorAddition(int index, glm::vec3 color);
	bool approxEqual(glm::vec3 a, glm::vec3 b, float epsilon);
	void updateWayPoints(double delta);
	void initWayPoints();
	void addTrafficLight(std::string id, int index, int weight, int status);
	void removeCarObject(int index);
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
	void updateTest(const double currentframetime);
};