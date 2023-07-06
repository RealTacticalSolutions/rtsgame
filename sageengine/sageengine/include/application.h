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

	int lastLevel = 0;
	bool rotateZ = true;

	void checkLevel();
	void loadLevel(int level);

	void Level1();
	void Level2();
	void Level3();
	void Level4();
public:
	
	application() : camera(DEFAULT_CAM_POS, DEFAULT_CAM_LOOK_POS, DEFAULT_CAM_UP_POS, DEFAULT_FOV, DEFAULT_NEAR_CLIPPING_PLANE, DEFAULT_FAR_CLIPPING_PLANE), scene()
	{
	};
	~application()
	{
	};

	
	/*
	 * @brief Constructs game objects for the application.
	 */
	void constructGameobjects();

	/*
	 * @brief Initializes the window for the application.
	 */
	void initWindow();

	/*
	 * @brief Starts the application.
	 */
	void start();

	/*
	 * @brief The main loop of the application.
	 */
	void mainLoop();

	/*
	 * @brief Draws a frame of the application.
	 */
	void drawFrame();

	/*
	 * @brief Cleans up resources and performs cleanup tasks.
	 */
	void cleanup();

	/*
	 * @brief Loads a model from a specified path.
	 *
	 * @param path The path to the model file.
	 * @return The loaded model as a Mesh object.
	 */
	Mesh loadModel(char* path);

};