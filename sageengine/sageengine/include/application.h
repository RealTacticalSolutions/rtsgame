#pragma once



class window;

class application {
private:

	const uint32_t WIDTH = 1280;
	const uint32_t HEIGHT = 720;

	const glm::vec3 DEFAULT_CAM_POS = glm::vec3(1.0f, 0.0f, 2.0f);
	const glm::vec3 DEFAULT_CAM_LOOK_POS = glm::vec3(0.0f, 0.0f, 0.0f);
	const glm::vec3 DEFAULT_CAM_UP_POS = glm::vec3(0.0f, 0.0f, 1.0f);
	const float DEFAULT_FOV = glm::radians(45.0f);
	const float DEFAULT_NEAR_CLIPPING_PLANE = 0.1f;
	const float DEFAULT_FAR_CLIPPING_PLANE = 100.0f;

	int indexOffset = 0;
	
	std::unique_ptr<renderer> vulkanrenderer;
	std::unique_ptr<window> windowObject;

	Scene scene;
	Camera camera;
	std::vector<messageObject> message;

	std::vector<WayPoints> paths;
	std::vector<WayPoints*> bikepaths;

	glm::vec3 spawnpoint = glm::vec3(0.34f,-1.0f,1.0f);

	std::vector<TrafficLight> lights;

	std::vector<glm::vec3> lightspos =
	{ 
	glm::vec3(4.102f, -0.116f,1.0f),//1.1
	glm::vec3(2.70f, -0.062f,1.0f),//2.1
	glm::vec3(4.200f, 0.200f,1.0f),//42.0 
	glm::vec3(0.406f, 3.417f,1.0f),//12.1
	glm::vec3(-0.128f, 3.550f,1.0f),//11.1
	glm::vec3(-0.535f, 3.647f,1.0f),//10.1 
	glm::vec3(-3.323f, 2.153f,1.0f),//9.1 
	glm::vec3(-3.424f, 1.893f,1.0f),//8.1 
	glm::vec3(-3.544f, 1.600f,1.0f),//7.1 
	glm::vec3(1.105f, -3.723f,1.0f),//6.1 
	glm::vec3(1.490f, -3.670f,1.0f),//5.1 

	glm::vec3(-2.700f, 2.260f,1.0f),//36.1
	glm::vec3(-2.423f, 2.895f,1.0f),//36.2
	glm::vec3(-3.363f, 1.336f,1.0f),//35.1
	glm::vec3(-2.950f, 2.324f,1.0f),//35.2
	glm::vec3(-2.660f, 1.169f,1.0f),//86.1
	glm::vec3(-2.334f, 2.735f,1.0f),//26.1
	glm::vec3(-1.042f, 3.045f,1.0f),//88.1
	glm::vec3(1.359f, 2.610f,1.0f),//28.1
	glm::vec3(0.842f, 3.139f,1.0f),//37.1
	glm::vec3(-0.834f, 3.548f,1.0f),//37.2
	glm::vec3(0.742f, 2.869f,1.0f),//38.1
	glm::vec3(1.487f, 2.680f,1.0f),//38.2
	glm::vec3(2.176f, -1.453f,1.0f),//22.0
	glm::vec3(2.592f, -0.275f,1.0f),//31.1
	glm::vec3(2.408f, 0.826f,1.0f),//31.2
	glm::vec3(2.420f, -1.513f,1.0f),//32.1
	glm::vec3(2.212f, -0.138f,1.0f),//32.2

	};

	void updateColor(int index, glm::vec3 color);
	void updateColorAddition(int index, glm::vec3 color);
	bool approxEqual(glm::vec3 a, glm::vec3 b, float epsilon);
	void updateWayPoints(double delta);
	void updateWayPointsBikes(double delta);
	void updateWayPointsPeople(double delta);
	void initWayPoints();
	void addTrafficLight(std::string id, int index, double weight, int status);
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