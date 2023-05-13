#pragma once



class window;

class application {
private:

	const uint32_t WIDTH = 1280;
	const uint32_t HEIGHT = 720;

	const glm::vec3 DEFAULT_CAM_POS = glm::vec3(0.0f, 0.0f, 0.0f);
	const glm::vec3 DEFAULT_CAM_LOOK_POS = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 DEFAULT_CAM_UP_POS = glm::vec3(0.0f, 0.0f, 1.0f);
	const float DEFAULT_FOV = glm::radians(45.0f);
	const float DEFAULT_NEAR_CLIPPING_PLANE = 0.1f;

	const float DEFAULT_FAR_CLIPPING_PLANE = 1000.0f;


	int indexOffset = 0;
	
	std::unique_ptr<renderer> vulkanrenderer;
	std::unique_ptr<window> windowObject;

	Scene scene;
	Camera camera;
	std::vector<messageObject> message;
	TimerObject timer;

	std::vector<WayPoints*> paths;
	std::vector<WayPoints*> bikepaths;
	std::vector<WayPoints*> trainpaths;

	glm::vec3 spawnpoint = glm::vec3(0.34f,-1.0f,1.0f);

	std::vector<TrafficLight> lights;
	float z = 1.0f;
	std::vector<glm::vec3> lightspos =
	{ 
	glm::vec3(4.102f, -0.116f,z),//1.1
	glm::vec3(2.70f, -0.062f,z),//2.1
	glm::vec3(4.200f, 0.200f,z),//42.0 
	glm::vec3(0.406f, 3.417f,z),//12.1
	glm::vec3(-0.128f, 3.550f,z),//11.1
	glm::vec3(-0.535f, 3.647f,z),//10.1 
	glm::vec3(-3.323f, 2.153f,z),//9.1 
	glm::vec3(-3.424f, 1.893f,z),//8.1 
	glm::vec3(-3.544f, 1.600f,z),//7.1 
	glm::vec3(1.105f, -3.723f,z),//6.1 
	glm::vec3(1.490f, -3.670f,z),//5.1 

	glm::vec3(-2.700f, 2.260f,z),//36.1
	glm::vec3(-2.423f, 2.895f,z),//36.2
	glm::vec3(-3.363f, 1.336f,z),//35.1
	glm::vec3(-2.950f, 2.324f,z),//35.2
	glm::vec3(-2.660f, 1.169f,z),//86.1
	glm::vec3(-2.334f, 2.735f,z),//26.1
	glm::vec3(-1.042f, 3.045f,z),//88.1
	glm::vec3(1.359f, 2.610f,z),//28.1
	glm::vec3(0.842f, 3.139f,z),//37.1
	glm::vec3(-0.834f, 3.548f,z),//37.2
	glm::vec3(0.742f, 2.869f,z),//38.1
	glm::vec3(1.487f, 2.680f,z),//38.2
	glm::vec3(2.176f, -1.453f,z),//22.0
	glm::vec3(2.592f, -0.275f,z),//31.1
	glm::vec3(2.408f, 0.826f,z),//31.2
	glm::vec3(2.420f, -1.513f,z),//32.1
	glm::vec3(2.212f, -0.138f,z),//32.2
	glm::vec3(5.194f, -2.646f,z), //160
	glm::vec3(-1.136f, -2.623f,z), //152
	glm::vec3(-1.1312f, -2.89195f,z ), //154
	glm::vec3(1.020f, -2.750f,z) //99.0
	};

	void updateColor(int index, glm::vec3 color);
	void updateColorAddition(int index, glm::vec3 color);
	bool approxEqual(glm::vec3 a, glm::vec3 b, float epsilon);
	void updateWayPoints(double delta);
	void updateWayPointsBikes(double delta);
	void updateWayPointsTrain(double delta);
	void updateWayPointsPeople(double delta);
	void initWayPoints();
	void addTrafficLight(std::string id, int index, int weight, int status);
	void removeCarObject(int index);
	void updateLightWeights();
	void addWeight(std::string id);
	void removeWeight(std::string id);
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

	Mesh loadModel(char* path);

};