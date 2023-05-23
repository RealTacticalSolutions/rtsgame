#include "pch.h"
#include "application.h"
#include "CROSSROAD/pchroads.h"
#include "color.h"
#include "CROSSROAD/crossroadlevel.h"

#include <random>
static double lastSpawnTimeCar = 0.0;
static double lastSpawnTimeBike = 0.0;
static double lastSpawnTimeTrain = 0.0;
static double lastSpawnTimeBus = 0.0;
static double lastSpawnTimePeople = 0.0;
const int maxinstances = 200;
static int carcount = 2;
static int bikecount = 0;
static int traincount = 0;
static int buscount = 0;
static int peoplecount = 0;

const float EPSILON = 0.1f;
const float VELOCITY = 120.0f;

std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator

std::uniform_int_distribution<> dicar(0, 10); // define the range
std::uniform_int_distribution<> dibike(0, 4); // define the range
std::uniform_int_distribution<> ditrain(0, 2); // define the range
std::uniform_int_distribution<> displit(0, 1); // define the range
std::uniform_int_distribution<> dipeople(0, 3); // define the range

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

void application::mainLoop()
{
	CrossRoadLevel level(message, timer, scene.gameObjects, lights);

    float cameraSpeed = 2.0f;
    float sensitivity = 0.1f;
    glm::vec2 centerPos = glm::vec2(WIDTH, HEIGHT) / 2.0f;
    glm::vec2 lastCursorPos = centerPos;	
	

	double lastFrameTime = glfwGetTime();
	double lastSecondTime = lastFrameTime;
	int fps = 0;
	char windowTitle[256];
	Input input = Input(windowObject.get()->getWindow());
	level.init();
	while (!windowObject->shouldClose())
	{
		double currentFrameTime = glfwGetTime();
		double delta = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;
		
		
		//updateColorAddition(0, glm::vec3(0.0001f, 0.0001f, 0.0001f));
		glfwPollEvents();

		level.mainLoop();
		updateTest(currentFrameTime);
		updateWayPoints(delta);
		updateWayPointsBikes(delta);
		updateWayPointsTrain(delta);
		updateLightWeights();
		drawFrame();

		


		fps++;
		if (currentFrameTime - lastSecondTime >= 1.0)
		{
			snprintf(windowTitle, 256, "FPS: %d", fps);
			glfwSetWindowTitle(windowObject->getWindow(), windowTitle);
			fps = 0;
			lastSecondTime = currentFrameTime;
		}
	
	
		glm::vec2 cursorPos = input.getCursorPos();
        bool spacePressed = input.keyDown(GLFW_KEY_SPACE);
        bool ePressed = input.keyDown(GLFW_KEY_E);
        bool isRotating = input.mouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT);
        bool isLookingAt = input.mouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT);

        bool w = input.keyPressed(GLFW_KEY_W);
        bool a = input.keyPressed(GLFW_KEY_A);
        bool s = input.keyPressed(GLFW_KEY_S);
        bool d = input.keyPressed(GLFW_KEY_D);

        input.updateInput();
        //camera.rotateCamera(0.005f);

        // Move camera position using WASD keys
        if (w)
        {
            camera.moveForward(delta, cameraSpeed);
        }
        if (a)
        {
            camera.moveLeft(delta, cameraSpeed );
        }
        if (s)
        {
            camera.moveBackward(delta, cameraSpeed );
        }
        if (d)
        {
            camera.moveRight(delta, cameraSpeed );
        }

        if (spacePressed) {
            int width = 0, height = 0;
            glfwGetFramebufferSize(windowObject.get()->getWindow(), &width, &height);
            glm::vec3 worldpos = GameMath::windowToWorldPos(cursorPos, glm::vec2(width, height), camera);

            glm::vec3 direction = worldpos - camera.position;
            
            scene.renderer.get()->initRaycast(camera.position, direction);
            
        }

        if (ePressed) {
            glm::mat4 matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.1f, -0.5f, 0.0f));
            scene.instantiateObject(scene.bluePrints[4], matrix, glm::vec3(0.6f));
            scene.renderer.get()->addInstance(matrix);
        }

        glm::vec2 cursorDelta = cursorPos - lastCursorPos;
        lastCursorPos = cursorPos;

        if (isLookingAt)
        {
            camera.moveLookAt(cursorDelta, sensitivity);
        }


        fps++;
        if (currentFrameTime - lastSecondTime >= 1.0)
        {                   
            snprintf(windowTitle, 256, "FPS: %d", fps);
            glfwSetWindowTitle(windowObject->getWindow(), windowTitle);
            fps = 0;
            lastSecondTime = currentFrameTime;
        }
    }
    vkDeviceWaitIdle(scene.renderer->getDevice());

	level.cleanup();

}

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}

void application::drawFrame()
{
	scene.renderer->renderer::drawFrame(windowObject->getWindow());
}
void application::updateColor(int index, glm::vec3 color)
{
	scene.gameObjects[index]->properties.color = color;
};
void application::updateColorAddition(int index, glm::vec3 color)
{
	scene.gameObjects[index]->properties.color = scene.gameObjects[index]->properties.color + color;
};

void application::constructGameobjects()
{
	scene.renderObjects.reserve(10);


	scene.blueprintObject(ShapeTool::createRectangle(3.2f, 1.8f), "../../../textures/kruispunt.png");

	scene.blueprintObject(ShapeTool::createSquare(0.07f), "../../../textures/light.jpg");

    //scene.blueprintObject(ShapeTool::createSquare(3.0f), "../../../textures/1.jpg");

    //scene.blueprintObject(ShapeTool::createSquare(0.01f));

	

	scene.blueprintObject(loadModel("../../../models/car.obj"));

	//scene.blueprintObject(ShapeTool::createSquare(0.05f), "../../../textures/car.jpg");

	scene.blueprintObject(ShapeTool::createSquare(0.05f), "../../../textures/bike.jpg");

	scene.blueprintObject(loadModel("../../../models/room.obj"), "../../../textures/room.png");

	scene.blueprintObject(loadModel("../../../models/train.obj"));

	scene.blueprintObject(ShapeTool::createSquare(0.05f), "../../../textures/1.jpg");
	

	/* glm::vec4 gridStart = glm::vec4(scene.gameObjects[0].mesh.vertices[0].pos, 1.0f) * scene.gameObjects[0].properties.transform;
	 glm::vec4 gridEnd = glm::vec4(scene.gameObjects[0].mesh.vertices[2].pos, 1.0f) * scene.gameObjects[0].properties.transform;
	 float cellCount = 1;

	 scene.blueprintObject(ShapeTool::generateGrid(gridStart, gridEnd, cellCount));*/
}

void application::initWindow()
{
    constructGameobjects();
	initWayPoints();
    start();
    int objectCount = scene.bluePrints.size();
    camera.setPosition(glm::vec3(0.0f, 0.0f, 15.0f));
    camera.setLookPosition(glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f,1.0f,0.0f));
    //camera.rotateCamera(180.0f);
	vulkanrenderer = std::make_unique<renderer>(camera, objectCount, scene.renderObjects, scene.gameObjects);
	windowObject = std::make_unique<window>(WIDTH, HEIGHT, vulkanrenderer.get());

	vulkanrenderer->initVulkan(std::move(windowObject));
    scene.renderer = std::move(vulkanrenderer);

}

void application::start()
{

	scene.instantiateObject(scene.bluePrints[0], glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f)), glm::vec3(1.0f, 1.0f, 1.0f));

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[0]), glm::vec3(1.0f, 0.0f, 0.0f)); //1.1
	addTrafficLight("1.1", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[1]), glm::vec3(1.0f, 0.0f, 0.0f)); //2.1
	addTrafficLight("2.1", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[2]), glm::vec3(1.0f, 0.0f, 0.0f)); //42.0
	addTrafficLight("42.0", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[3]), glm::vec3(1.0f, 0.0f, 0.0f)); //12.1
	addTrafficLight("12.1", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[4]), glm::vec3(1.0f, 0.0f, 0.0f)); //11.1
	addTrafficLight("11.1", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[5]), glm::vec3(1.0f, 0.0f, 0.0f)); //10.1
	addTrafficLight("10.1", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[6]), glm::vec3(1.0f, 0.0f, 0.0f)); //9.1
	addTrafficLight("9.1", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[7]), glm::vec3(1.0f, 0.0f, 0.0f)); //8.1
	addTrafficLight("8.1", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[8]), glm::vec3(1.0f, 0.0f, 0.0f)); //7.1
	addTrafficLight("7.1", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[9]), glm::vec3(1.0f, 0.0f, 0.0f)); //6.1
	addTrafficLight("6.1", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[10]), glm::vec3(1.0f, 0.0f, 0.0f)); //5.1
	addTrafficLight("5.1", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[11]), glm::vec3(1.0f, 0.0f, 0.0f)); //36.1
	addTrafficLight("36.1", scene.gameObjects.size() - 1, 0, 0);
	
	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[12]), glm::vec3(1.0f, 0.0f, 0.0f)); //36.2
	addTrafficLight("36.2", scene.gameObjects.size() - 1, 0, 0);
	
	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[13]), glm::vec3(1.0f, 0.0f, 0.0f)); //35.1
	addTrafficLight("35.1", scene.gameObjects.size() - 1, 0, 0);
	
	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[14]), glm::vec3(1.0f, 0.0f, 0.0f)); //35.2
	addTrafficLight("35.2", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[15]), glm::vec3(1.0f, 0.0f, 0.0f)); //86.1
	addTrafficLight("86.1", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[16]), glm::vec3(1.0f, 0.0f, 0.0f)); //26.1
	addTrafficLight("26.1", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[17]), glm::vec3(1.0f, 0.0f, 0.0f)); //88.1
	addTrafficLight("88.1", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[18]), glm::vec3(1.0f, 0.0f, 0.0f)); //28.1
	addTrafficLight("28.1", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[19]), glm::vec3(1.0f, 0.0f, 0.0f)); //37.1
	addTrafficLight("37.1", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[20]), glm::vec3(1.0f, 0.0f, 0.0f)); //37.2
	addTrafficLight("37.2", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[21]), glm::vec3(1.0f, 0.0f, 0.0f)); //38.1
	addTrafficLight("38.1", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[22]), glm::vec3(1.0f, 0.0f, 0.0f)); //38.2
	addTrafficLight("38.2", scene.gameObjects.size() - 1, 0, 0);
	
	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[23]), glm::vec3(1.0f, 0.0f, 0.0f)); //22.0
	addTrafficLight("22.0", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[24]), glm::vec3(1.0f, 0.0f, 0.0f)); //31.1
	addTrafficLight("31.1", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[25]), glm::vec3(1.0f, 0.0f, 0.0f)); //31.2
	addTrafficLight("31.2", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[26]), glm::vec3(1.0f, 0.0f, 0.0f)); //32.1
	addTrafficLight("32.1", scene.gameObjects.size() - 1, 0, 0);
	
	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[27]), glm::vec3(1.0f, 0.0f, 0.0f)); //32.2
	addTrafficLight("32.2", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[28]), glm::vec3(1.0f, 0.0f, 0.0f)); //160.2
	addTrafficLight("160.0", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[29]), glm::vec3(1.0f, 0.0f, 0.0f)); //152.2
	addTrafficLight("152.0", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[30]), glm::vec3(1.0f, 0.0f, 0.0f)); //154.2
	addTrafficLight("154.0", scene.gameObjects.size() - 1, 0, 0);

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), lightspos[31]), glm::vec3(1.0f, 0.0f, 0.0f)); //99.0
	addTrafficLight("99.0", scene.gameObjects.size() - 1, 0, 0);


	//scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,2.0f)), glm::vec3(1.0f, 1.0f, 1.0f));


	spawnpoint = trainpaths[1]->getWayPointPosition(0);
	scene.instantiateTrain(scene.bluePrints[5], glm::scale(glm::translate(glm::mat4(1.0f), spawnpoint), glm::vec3(0.005f, 0.005f, 0.005f)), glm::vec3(1.0f, 1.0f, 0.0f), trainpaths[1]);
	traincount += 1;

	////spawnpoint = paths[1].getWayPointPosition(0);
	//spawnpoint = glm::vec3(1.0f, 0.0f, 1.0f);
	//scene.instantiateObject(scene.bluePrints[2], glm::translate(glm::mat4(1.0f), spawnpoint), glm::vec3(1.0f, 1.0f, 1.0f));
	//cars.push_back(car{ static_cast<int>(scene.gameObjects.size() - 1), 0, paths[1] });

}

void application::cleanup()
{
}

Mesh application::loadModel(char* path) {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path)) {
        throw std::runtime_error(warn + err);
    }

    std::unordered_map<Vertex, uint32_t> uniqueVertices{};

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex{};

            vertex.pos = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.texCoord = {
                attrib.texcoords[2 * index.texcoord_index + 0],
                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };

            vertex.color = { 1.0f, 1.0f, 1.0f };

            if (index.normal_index >= 0) {
                vertex.normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
                };
            }
           
            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                vertices.push_back(vertex);
            }

            indices.push_back(uniqueVertices[vertex]);
        }
    }

    return Mesh({
        vertices, indices
    });
}


void application::updateTest(const double currentFrameTime)
{
	if (carcount < 60 && 0.1 < (currentFrameTime - lastSpawnTimeCar))
	{
		int pathindex = dicar(gen);
		if (pathindex == 2)
		{
			if (buscount < 1 && 120 < (currentFrameTime - lastSpawnTimeBus))
			{
				spawnpoint = paths[pathindex]->getWayPointPosition(0);
				scene.instantiateCar(scene.bluePrints[2], glm::scale(glm::translate(glm::mat4(1.0f), spawnpoint), glm::vec3(0.005f, 0.005f, 0.005f)), glm::vec3(1.0f, 1.0f, 0.0f), paths[pathindex], glm::vec3(0.005f, 0.005f, 0.005f));

				lastSpawnTimeBus = currentFrameTime;
				buscount += 1;
			}
		}
		else
		{
			spawnpoint = paths[pathindex]->getWayPointPosition(0);
			//scene.instantiateCar(scene.bluePrints[2], glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.005f, 0.005f, 0.005f)), spawnpoint * glm::vec3(100.0f)), glm::vec3(1.0f, 1.0f, 0.0f), paths[pathindex]);
			scene.instantiateCar(scene.bluePrints[2], glm::scale(glm::translate(glm::mat4(1.0f), spawnpoint), glm::vec3(0.005f, 0.005f, 0.005f)), glm::vec3(1.0f, 1.0f, 0.0f), paths[pathindex], glm::vec3(0.005f, 0.005f, 0.005f));

			lastSpawnTimeCar = currentFrameTime;
			carcount += 1;
		}
		
	}

	if (bikecount < 100 && 0.1 < (currentFrameTime - lastSpawnTimeBike))
	{
		int pathindex = dibike(gen);
		//pathindex = 3;
		spawnpoint = bikepaths[pathindex]->getWayPointPosition(0);
		scene.instantiateBike(scene.bluePrints[3], glm::translate(glm::mat4(1.0f), spawnpoint), glm::vec3(1.0f, 1.0f, 0.0f), bikepaths[pathindex]);
		lastSpawnTimeBike = currentFrameTime;
		bikecount += 1;
	}

	if (traincount < 1 && 180 < (currentFrameTime - lastSpawnTimeTrain))
	{
		int pathindex = ditrain(gen);
		spawnpoint = trainpaths[pathindex]->getWayPointPosition(0);
		scene.instantiateTrain(scene.bluePrints[5], glm::scale(glm::translate(glm::mat4(1.0f), spawnpoint), glm::vec3(0.005f, 0.005f, 0.005f)), glm::vec3(1.0f, 1.0f, 0.0f), trainpaths[pathindex]);
		lastSpawnTimeTrain = currentFrameTime;
		traincount += 1;
	}

	if (peoplecount < 130 && 0.5 < (currentFrameTime - lastSpawnTimePeople))
	{
		int pathindex = dipeople(gen);
		spawnpoint = peoplepaths[pathindex]->getWayPointPosition(0);
		scene.instantiateBike(scene.bluePrints[6], glm::translate(glm::mat4(1.0f), spawnpoint), glm::vec3(1.0f, 1.0f, 0.0f), peoplepaths[pathindex]);
		lastSpawnTimePeople = currentFrameTime;
		bikecount += 1;
	}

}


bool application::approxEqual(glm::vec3 a, glm::vec3 b, float epsilon)
{
	return glm::all(glm::lessThanEqual(glm::abs(a - b), glm::vec3(epsilon)));
}

// Updates cars waypoints
void application::updateWayPoints(double delta)
{
	if (scene.gameObjects.empty())
	{
		return;
	}

	std::vector<std::pair<size_t, Car*>> cars;
	for (size_t i = 0; i < scene.gameObjects.size(); i++)
	{
		if (Car* car = dynamic_cast<Car*>(scene.gameObjects[i].get()))
		{
			cars.emplace_back(i, car);
		}
	}

	std::vector<int> carstoremove;
	for (auto& [index, car] : cars)
	{

		if (car->getWayPointSize() < 1)
		{
			throw std::runtime_error("Waypoint index must be not < 1");
		}
		// Get current waypoint (target)
		int currentpoint = car->getCurrentWayPoint();

		// Set the target position
		WayPoints* waypoints = car->getWayPoints();


		glm::vec3 target(waypoints->getWayPointPosition(currentpoint).x, waypoints->getWayPointPosition(currentpoint).y, 0.0f);

		// Get the current position of the object
		glm::vec3 position = glm::vec3(car->properties.transform[3]);

		// Calculate the direction from the current position to the target position
		glm::vec3 direction;
		if (glm::length(position - target) != 0.0f) {
			direction = glm::normalize(target - position);
		}
		else {
			// Handle the case where position and target are the same vector
			direction = glm::vec3(0.000001f); // set direction to a default value
			// Todo:: causes some bugs when reaching endpoint removing alot of once for exmaple
		}

		// Set the velocity
		float velocity = VELOCITY * (delta / 60);

		// Calculate the new position based on the direction and velocity
		glm::vec3 new_pos = position + direction * velocity;

		// Calculate the rotation angle based on the direction
		float rotation_angle = atan2(direction.y, direction.x);

		rotation_angle += glm::radians(-90.0f); // Rotate by 90 degrees around the Z-axis


		bool removed = false;
		if (approxEqual(position, target, EPSILON))
		{

			WayPointType pointType = waypoints->getEnum(currentpoint);

			std::string lightid;
			int nextwaypoint;
			WayPoint test = waypoints->getWayPoint(currentpoint);
			int nextindex = displit(rd);


			switch (pointType)
			{
			case General:
					car->setCurrentWayPoint(currentpoint + 1);
				break;
			case EndPoint:
				carstoremove.push_back(index);
				removed = true;
				break;
			case SplitPoint:
				car->setWayPoint(test.getNewPath(nextindex));
				break;
			case TrafficPoint:
				lightid = waypoints->getLightId(currentpoint);
				if (!car->weightadded)
				{
					addWeight(lightid);
					car->weightadded = true;
				}
				//todo:: also remove from weight
				
				if (!(lightid == "-1"))
				{
					if (scene.gameObjects[getId(lights, lightid)]->properties.color == getColor(RED))
					{
						continue;
					}
					else
					{
						removeWeight(lightid);
						car->setCurrentWayPoint(currentpoint + 1);
						car->weightadded = false;
					}
				}
				break;
			default:
				//scene.gameObjects[index].properties.transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 1.0f));
				break;
			}
		}
		if (!removed)
		{
			//scene.gameObjects[index]->properties.transform = glm::scale(glm::translate(glm::mat4(1.0f), new_pos), glm::vec3(0.005f, 0.005f, 0.005f));
			//car->properties.transform = glm::scale(glm::translate(glm::mat4(1.0f), new_pos), glm::vec3(0.005f, 0.005f, 0.005f));

			car->properties.transform = glm::translate(glm::mat4(1.0f), new_pos);
			car->properties.transform = glm::rotate(car->properties.transform, rotation_angle, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around Z-axis
			car->properties.transform = glm::scale(car->properties.transform, car->scale);
			car->SetUpVector(glm::vec3(0.0f, 1.0f, 0.0f)); // Set the up vector
			car->SetRightVector(glm::vec3(1.0f, 0.0f, 0.0f)); // Set the right vector
		}
	}

	for (size_t i = 0; i < carstoremove.size(); i++)
	{
		scene.removeObject(carstoremove[i]);
		carcount -= 1;
	}

}


// Updates Train waypoints
void application::updateWayPointsTrain(double delta)
{
	if (scene.gameObjects.empty())
	{
		return;
	}

	std::vector<std::pair<size_t, Train*>> trains;
	for (size_t i = 0; i < scene.gameObjects.size(); i++)
	{
		if (Train* train = dynamic_cast<Train*>(scene.gameObjects[i].get()))
		{
			trains.emplace_back(i, train);
		}
	}

	std::vector<int> trainstoremove;
	for (auto& [index, train] : trains)
	{

		if (train->getWayPointSize() < 1)
		{
			throw std::runtime_error("Waypoint index must be not < 1");
		}
		// Get current waypoint (target)
		int currentpoint = train->getCurrentWayPoint();

		// Set the target position
		WayPoints* waypoints = train->getWayPoints();


		glm::vec3 target(waypoints->getWayPointPosition(currentpoint).x, waypoints->getWayPointPosition(currentpoint).y, 0.0f);

		// Get the current position of the object
		glm::vec3 position = glm::vec3(train->properties.transform[3]);

		// Calculate the direction from the current position to the target position
		glm::vec3 direction;
		if (glm::length(position - target) != 0.0f) {
			direction = glm::normalize(target - position);
		}
		else {
			// Handle the case where position and target are the same vector
			direction = glm::vec3(0.000001f); // set direction to a default value
			// Todo:: causes some bugs when reaching endpoint removing alot of once for exmaple
		}

		// Set the velocity
		float velocity = VELOCITY * (delta / 60);

		// Calculate the new position based on the direction and velocity
		glm::vec3 new_pos = position + direction * velocity;


		bool removed = false;
		if (approxEqual(position, target, EPSILON))
		{

			WayPointType pointType = waypoints->getEnum(currentpoint);

			std::string lightid;
			int nextwaypoint;
			WayPoint test = waypoints->getWayPoint(currentpoint);
			int nextindex = displit(rd);


			switch (pointType)
			{
			case General:
					train->setCurrentWayPoint(currentpoint + 1);
					break;
			case EndPoint:
				removeWeight(lightid);
				trainstoremove.push_back(index);
				removed = true;
				break;
			case SplitPoint:
				train->setWayPoint(test.getNewPath(nextindex));
				break;
			case TrafficPoint:
				lightid = waypoints->getLightId(currentpoint);
				if (!train->weightadded)
				{
					addWeight(lightid);
					train->weightadded = true;
				}
				//todo:: also remove from weight
				
				if (!(lightid == "-1"))
				{
					if (scene.gameObjects[getId(lights, lightid)]->properties.color == getColor(RED))
					{
						continue;
					}
					else
					{

						train->setCurrentWayPoint(currentpoint + 1);
						removeWeight(lightid);
						train->weightadded = false;
					}
				}
				break;
			default:
				//scene.gameObjects[index].properties.transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 1.0f));
				break;
			}
		}
		if (!removed)
		{
			scene.gameObjects[index]->properties.transform = glm::scale(glm::translate(glm::mat4(1.0f), new_pos), glm::vec3(0.005f, 0.005f, 0.005f));
		}
	}

	for (size_t i = 0; i < trainstoremove.size(); i++)
	{
		scene.removeObject(trainstoremove[i]);
		traincount -= 1;
	}

}
// Updates bike waypoints
void application::updateWayPointsBikes(double delta)
{
	if (scene.gameObjects.empty())
	{
		return;
	}

	std::vector<std::pair<size_t, Bike*>> bikes;
	for (size_t i = 0; i < scene.gameObjects.size(); i++)
	{
		if (Bike* bike = dynamic_cast<Bike*>(scene.gameObjects[i].get())) 
		{
			bikes.emplace_back(i, bike);
		}
	}

	std::vector<int> bikestoremove;
	for (auto& [index, bike] : bikes)
	{

		if (bike->getWayPointSize() < 1)
		{
			throw std::runtime_error("Waypoint index must be not < 1");
		}
		// Get current waypoint (target)
		int currentpoint = bike->getCurrentWayPoint();

		// Set the target position
		WayPoints* waypoints = bike->getWayPoints();


		glm::vec3 target(waypoints->getWayPointPosition(currentpoint).x, waypoints->getWayPointPosition(currentpoint).y, 0.1f);

		// Get the current position of the object
		glm::vec3 position = glm::vec3(bike->properties.transform[3]);

		// Calculate the direction from the current position to the target position
		glm::vec3 direction;
		if (glm::length(position - target) != 0.0f) {
			direction = glm::normalize(target - position);
		}
		else {
			// Handle the case where position and target are the same vector
			direction = glm::vec3(0.000001f); // set direction to a default value
			// Todo:: causes some bugs when reaching endpoint removing alot of once for exmaple
		}

		// Set the velocity
		float velocity = (VELOCITY/1.5) * (delta / 60);

		// Calculate the new position based on the direction and velocity
		glm::vec3 new_pos = position + direction * velocity;
		

		bool removed = false;
		if (approxEqual(position, target, EPSILON))
		{

			WayPointType pointType = waypoints->getEnum(currentpoint);

			std::string lightid;
			int nextwaypoint;
			WayPoint test = waypoints->getWayPoint(currentpoint);
			int nextindex = displit(rd);


			switch (pointType)
			{
			case General:
					bike->setCurrentWayPoint(currentpoint + 1);
				break;
			case EndPoint:
				bikestoremove.push_back(index);
				removed = true;
				break;
			case SplitPoint:
				bike->setWayPoint(test.getNewPath(nextindex));
				break;
			case TrafficPoint:
				lightid = waypoints->getLightId(currentpoint);
				if (!bike->weightadded)
				{
					addWeight(lightid);
					bike->weightadded = true;
				}
				//todo:: also remove from weight
				
				if (!(lightid == "-1"))
				{
					if (scene.gameObjects[getId(lights, lightid)]->properties.color == getColor(RED))
					{
						continue;
					}
					else
					{
						bike->setCurrentWayPoint(currentpoint + 1);
						removeWeight(lightid);
						bike->weightadded = false;
					}
				}
				break;
			default:
				//scene.gameObjects[index].properties.transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 1.0f));
				break;
			}
		}
		if(!removed)
		{
			scene.gameObjects[index]->properties.transform = glm::translate(glm::mat4(1.0f), new_pos);
		}
	}

	for (size_t i = 0; i < bikestoremove.size(); i++)
	{
		scene.removeObject(bikestoremove[i]);
		bikecount -= 1;
	}
	
}
void application::initWayPoints()
{	

	float z = 0.01f;
	/*1.1*/std::vector<WayPoint> waypoints0 = { 
		WayPoint(glm::vec3(8.900f, -0.700f, z)),
		WayPoint(glm::vec3(7.4478754277318, -0.6424615826693, z)),
		WayPoint(glm::vec3(6.2655008610581, -0.5189857576686, z)),
		WayPoint(glm::vec3(5.2365356527187, -0.3543513243343, z)),
		WayPoint(lightspos[0], TrafficPoint,"1.1"),
		WayPoint(glm::vec3(3.3427633065728, 0.1018627834836, z)),
		WayPoint(glm::vec3(2.1123779288658, 0.4602762711748, z)),
		WayPoint(glm::vec3(1.3160580937782, 0.8873932736309, z)),
		WayPoint(glm::vec3(0.8756129718504, 1.2858154516885, z)),
		WayPoint(glm::vec3(0.7087367039929, 1.7901965769456, z)),
		WayPoint(glm::vec3(0.8421507086444, 2.3470550311434, z)),
		WayPoint(glm::vec3(1.0625738467643, 2.9561189654222, z)),
		WayPoint(glm::vec3(1.2249908959054, 3.5361798552115, z)),
		WayPoint(glm::vec3(1.3874079450464, 4.0524340471241, z)),
		WayPoint(glm::vec3(1.5, 4.5, z)),
		WayPoint(glm::vec3(1.6476071514173, 4.9148711321509, z), EndPoint),
		};

	/*2.2*/std::vector<WayPoint> waypoints1 = {
		WayPoint(glm::vec3(8.8884344127193, -1.0405179236746,z)),
		WayPoint(glm::vec3(7.4326575402666, -0.9775453872072,z)),
		WayPoint(glm::vec3(6.2224943088012, -0.8660220713649,z)),
		WayPoint(glm::vec3(5.1626464011562, -0.6761999051331,z)),
		WayPoint(glm::vec3(4.0004148395579, -0.451847328123,z)),
		WayPoint(glm::vec3(3.2612318668167, -0.2322161308921,z)),
		WayPoint(lightspos[1], TrafficPoint,"2.1"),
		WayPoint(glm::vec3(2.1452134152702, 0.1408750779783,z)),
		WayPoint(glm::vec3(1.1848670970973, 0.5360175734766,z)),
		WayPoint(glm::vec3(0.4716218013583, 0.9954568477721,z)),
		WayPoint(glm::vec3(-0.1702132612523, 1.4263391275666,z)),
		WayPoint(glm::vec3(-0.861420251756, 1.9021049781731,z)),
		WayPoint(glm::vec3(-1.7612950821041, 2.2980994907728,z)),
		WayPoint(glm::vec3(-2.9670375511151, 2.6695367442597,z)),
		WayPoint(glm::vec3(-3.9996644447838, 2.9172218813602,z)),
		WayPoint(glm::vec3(-5.2610950837471, 2.9975677819311,z)),
		WayPoint(glm::vec3(-6.2734534309406, 2.9413256515315,z)),
		WayPoint(glm::vec3(-7.1652929272777, 2.8690143410177,z)),
		WayPoint(glm::vec3(-7.9767865230439, 2.8368759807893,z)),
		WayPoint(glm::vec3(-8.6539814206188, 2.7802355590692,z), EndPoint),
	};

	/*42.0*/std::vector<WayPoint> waypoints2 = {
		WayPoint(glm::vec3(8.9319992123494, -0.3680709702589, z)),
		WayPoint(glm::vec3(7.4912544025147, -0.3045805210119, z)),
		WayPoint(glm::vec3(6.3484263160696, -0.2069029067858, z)),
		WayPoint(glm::vec3(5.318416914837, -0.010425862561, z)),
		WayPoint(lightspos[2],TrafficPoint, "42.0"),
		WayPoint(glm::vec3(3.3919943110171, 0.3643813307881, z)),
		WayPoint(glm::vec3(2.7219530917216, 0.5014352165531, z)),
		WayPoint(glm::vec3(2.0444515233664, 0.656908353773, z)),
		WayPoint(glm::vec3(1.2987120313702, 0.8011683918534, z)),
		WayPoint(glm::vec3(0.4716218013583, 0.9954568477721, z)),
		WayPoint(glm::vec3(-0.1702132612523, 1.4263391275666, z)),
		WayPoint(glm::vec3(-0.861420251756, 1.9021049781731, z)),
		WayPoint(glm::vec3(-1.7612950821041, 2.2980994907728, z)),
		WayPoint(glm::vec3(-2.9670375511151, 2.6695367442597, z)),
		WayPoint(glm::vec3(-3.9996644447838, 2.9172218813602, z)),
		WayPoint(glm::vec3(-5.2610950837471, 2.9975677819311, z)),
		WayPoint(glm::vec3(-6.2734534309406, 2.9413256515315, z)),
		WayPoint(glm::vec3(-7.1652929272777, 2.8690143410177, z)),
		WayPoint(glm::vec3(-7.9767865230439, 2.8368759807893, z)),
		WayPoint(glm::vec3(-8.6539814206188, 2.7802355590692, z), EndPoint),
	};

	/*12.1*/std::vector<WayPoint> waypoints3 = {
		WayPoint(glm::vec3(0.8050734055799, 5.1258486936268, z)),
		WayPoint(glm::vec3(0.6828668579084, 4.8167380142225, z)),
		WayPoint(glm::vec3(0.5678489306882, 4.5004387143669, z)),
		WayPoint(glm::vec3(0.4456423830168, 4.1841394145114, z)),
		WayPoint(glm::vec3(0.3521903171504, 3.8534628737533, z)),
		WayPoint(lightspos[3],TrafficPoint, "12.1"),
		WayPoint(glm::vec3(0.0071365354898, 2.8398673901253, z)),
		WayPoint(glm::vec3(-0.1725789757918, 2.121005344999, z)),
		WayPoint(glm::vec3(-0.1006927712792, 0.9995805546021, z)),
		WayPoint(glm::vec3(0.5, 0.5, z)),
		WayPoint(glm::vec3(1.5167468302549, -0.1577873380512, z)),
		WayPoint(glm::vec3(2.8969619568972, -0.6250476673833, z)),
		WayPoint(glm::vec3(3.9150145814307, -0.9485812186457, z)),
		WayPoint(glm::vec3(5.0717994586123, -1.1533795633564, z)),
		WayPoint(glm::vec3(6.2216386423922, -1.3319260204651, z)),
		WayPoint(glm::vec3(7.5000312752903, -1.431912036446, z)),
		WayPoint(glm::vec3(8.9053226669936, -1.5835048929068, z), EndPoint),
	};

	/*11.1*/std::vector<WayPoint> waypoints4 = {
		WayPoint(glm::vec3(0.4669236053687, 5.1642258616477, z)),
		WayPoint(glm::vec3(0.2344505862627, 4.6262168745737, z)),
		WayPoint(glm::vec3(0, 4, z)),
		WayPoint(lightspos[4],TrafficPoint, "11.1"),
		WayPoint(glm::vec3(-0.3984978107211, 2.7101986259739, z)),
		WayPoint(glm::vec3(-0.496179609616, 2.371185323927, z)),
		WayPoint(glm::vec3(-0.5996073966811, 1.790840518728, z)),
		WayPoint(glm::vec3(-0.5847540684125, 1.2537304455903, z)),
		WayPoint(glm::vec3(-0.411610035793, 0.2086450894768, z)),
		WayPoint(glm::vec3(-0.1365356998153, -0.4790407504676, z)),
		WayPoint(glm::vec3(0.1179080609641, -1.2286183160069, z)),
		WayPoint(glm::vec3(0.2829526625507, -1.8956735807528, z), TrafficPoint , "99.0"),/* stoplicht alarm trein*/
		WayPoint(glm::vec3(0.4891385172183, -3.2306959961184, z)),
		WayPoint(glm::vec3(0.5995569026235, -4.136126756441, z)),
		WayPoint(glm::vec3(0.6731691595603, -4.8354431973405, z), EndPoint),
	};

	/*10.1*/std::vector<WayPoint> waypoints5 = {
		WayPoint(glm::vec3(-0.0253063308747, 5.1897813612963, z)),
		WayPoint(glm::vec3(-0.1649131931962, 4.6871966569388, z)),
		WayPoint(glm::vec3(-0.3254610848659, 4.247435040626, z)),
		WayPoint(lightspos[5],TrafficPoint, "10.1"),
		WayPoint(glm::vec3(-0.7722030442948, 2.9630519072679, z)),
		WayPoint(glm::vec3(-1.1212202000986, 2.6489364670445, z)),
		WayPoint(glm::vec3(-1.798313482358, 2.4674475460265, z)),
		WayPoint(glm::vec3(-2.9670375511151, 2.6695367442597, z)),
		WayPoint(glm::vec3(-3.9996644447838, 2.9172218813602, z)),
		WayPoint(glm::vec3(-5.2610950837471, 2.9975677819311, z)),
		WayPoint(glm::vec3(-6.2734534309406, 2.9413256515315, z)),
		WayPoint(glm::vec3(-7.1652929272777, 2.8690143410177, z)),
		WayPoint(glm::vec3(-7.9767865230439, 2.8368759807893, z)),
		WayPoint(glm::vec3(-8.6539814206188, 2.7802355590692, z), EndPoint),
	};

	/*9.1*/std::vector<WayPoint> waypoints6 = {
		WayPoint(glm::vec3(-8.9691922928002, 2.4267362142895, z)),
		WayPoint(glm::vec3(-8, 2.5, z)),
		WayPoint(glm::vec3(-6.7786220366297, 2.5245295292971, z)),
		WayPoint(glm::vec3(-5.2999163931711, 2.5150062509722, z)),
		WayPoint(glm::vec3(-4.3416053637149, 2.3747656125152, z)),
		WayPoint(lightspos[6],TrafficPoint, "9.1"),
		WayPoint(glm::vec3(-2.1639406497961, 1.8617126121981, z)),
		WayPoint(glm::vec3(-1.1382749591211, 1.4665019790939, z)),
		WayPoint(glm::vec3(0.0574076777885, 1.1628177737991, z)),
		WayPoint(glm::vec3(0.8287741504193, 1.6496024409932, z)),
		WayPoint(glm::vec3(0.9860430428974, 2.3198674827452, z)),
		WayPoint(glm::vec3(1.0625738467643, 2.9561189654222, z)),
		WayPoint(glm::vec3(1.2249908959054, 3.5361798552115, z)),
		WayPoint(glm::vec3(1.3874079450464, 4.0524340471241, z)),
		WayPoint(glm::vec3(1.5, 4.5, z)),
		WayPoint(glm::vec3(1.6476071514173, 4.9148711321509, z), EndPoint),
	};

	/*8.1*/std::vector<WayPoint> waypoints7 = {
		WayPoint(glm::vec3(-8.9780707032107, 2.1583753153014, z)),
		WayPoint(glm::vec3(-8.004874671439, 2.20703511689, z)),
		WayPoint(glm::vec3(-6.7762146813271, 2.2131175920885, z)),
		WayPoint(glm::vec3(-5.343248389402, 2.2229762623933, z)),
		WayPoint(glm::vec3(-4.399270258002, 2.1091351142144, z)),
		WayPoint(lightspos[7],TrafficPoint, "8.1"),
		WayPoint(glm::vec3(-2.2869957301227, 1.5459950739404, z)),
		WayPoint(glm::vec3(-1.2383506206657, 1.1278909894656, z)),
		WayPoint(glm::vec3(0.0127139351519, 0.4098887226485, z)),
		WayPoint(glm::vec3(1.4004623072924, -0.5387729565644, z)),
		WayPoint(glm::vec3(2.8887496340606, -1.1692631299271, z)),
		WayPoint(glm::vec3(3.866764134345, -1.4053972197196, z)),
		WayPoint(glm::vec3(5.0466861540049, -1.582958300348, z)),
		WayPoint(glm::vec3(6.2353914982127, -1.6954067884867, z)),
		WayPoint(glm::vec3(7.4997180666451, -1.7690467585517, z)),
		WayPoint(glm::vec3(8.8874737812391, -1.856144397543, z), EndPoint),
	};

	/*7.1*/std::vector<WayPoint> waypoints8 = {
		WayPoint(glm::vec3(-8.9799509541348, 1.8638907449656, z)),
		WayPoint(glm::vec3(-8.0092260770107, 1.9098422184389, z)),
		WayPoint(glm::vec3(-6.7915120299675, 1.8811225475181, z)),
		WayPoint(glm::vec3(-5.3476404158956, 1.8646852362819, z)),
		WayPoint(glm::vec3(-4.4729201713039, 1.8044710500736, z)),
		WayPoint(lightspos[8],TrafficPoint, "7.1"),
		WayPoint(glm::vec3(-2.4430587150794, 1.2529594145626, z)),
		WayPoint(glm::vec3(-1.2106040861149, 0.6939262654901, z)),
		WayPoint(glm::vec3(-0.1365356998153, -0.4790407504676, z)),
		WayPoint(glm::vec3(0.1179080609641, -1.2286183160069, z)),
		WayPoint(glm::vec3(0.2829526625507, -1.8956735807528, z)), /*stoplicht trein*/
		WayPoint(glm::vec3(0.4891385172183, -3.2306959961184, z)),
		WayPoint(glm::vec3(0.5995569026235, -4.136126756441, z)),
		WayPoint(glm::vec3(0.6731691595603, -4.8354431973405, z), EndPoint),
	};

	/*6.1*/std::vector<WayPoint> waypoints9 = {
		WayPoint(glm::vec3(1.3776995029531, -5.0033607423968, z)),
		WayPoint(glm::vec3(1.240331711901, -4.3623110508202, z)),
		WayPoint(lightspos[9],TrafficPoint, "6.1"),
		WayPoint(glm::vec3(0.8151456919778, -2.2363809512042, z)),
		WayPoint(glm::vec3(0.5991551629872, -1.1745396523912, z)),
		WayPoint(glm::vec3(0.3731326989372, -0.1527297628317, z)),
		WayPoint(glm::vec3(0.1730853724156, 0.6489100254638, z)),
		WayPoint(glm::vec3(0.0574076777885, 1.1628177737991, z)),
		WayPoint(glm::vec3(-0.1702132612523, 1.4263391275666, z)),
		WayPoint(glm::vec3(-0.861420251756, 1.9021049781731, z)),
		WayPoint(glm::vec3(-1.7612950821041, 2.2980994907728, z)),
		WayPoint(glm::vec3(-2.9670375511151, 2.6695367442597, z)),
		WayPoint(glm::vec3(-3.9996644447838, 2.9172218813602, z)),
		WayPoint(glm::vec3(-5.2610950837471, 2.9975677819311, z)),
		WayPoint(glm::vec3(-6.2734534309406, 2.9413256515315, z)),
		WayPoint(glm::vec3(-7.1652929272777, 2.8690143410177, z)),
		WayPoint(glm::vec3(-7.9767865230439, 2.8368759807893, z)),
		WayPoint(glm::vec3(-8.6539814206188, 2.7802355590692, z), EndPoint),
	};

	WayPoints* splitbottomstraight51 = new WayPoints
	({
		WayPoint(glm::vec3(1.0165189064083, -1.1373448322266,z)),
		WayPoint(glm::vec3(0.9059514575216, -0.4729394361205,z)),
		WayPoint(glm::vec3(0.8963982678125, 0.2362759914028,z)),
		WayPoint(glm::vec3(0.8, 0.8,z)),
		WayPoint(glm::vec3(0.8287741504193, 1.6496024409932,z)),
		WayPoint(glm::vec3(0.9860430428974, 2.3198674827452,z)),
		WayPoint(glm::vec3(1.0625738467643, 2.9561189654222, z)),
		WayPoint(glm::vec3(1.2249908959054, 3.5361798552115, z)),
		WayPoint(glm::vec3(1.3874079450464, 4.0524340471241, z)),
		WayPoint(glm::vec3(1.5, 4.5, z)),
		WayPoint(glm::vec3(1.6476071514173, 4.9148711321509, z), EndPoint),
		});
	WayPoints* splitbottomright51 = new WayPoints
	({	
		WayPoint(glm::vec3(1.5812641907014, -1.4308044560153, z)),
		WayPoint(glm::vec3(2.3360846157252, -1.0728039115754, z)),
		WayPoint(glm::vec3(2.8887496340606, -1.1692631299271, z)),
		WayPoint(glm::vec3(3.866764134345, -1.4053972197196, z)),
		WayPoint(glm::vec3(5.0466861540049, -1.582958300348, z)),
		WayPoint(glm::vec3(6.2353914982127, -1.6954067884867, z)),
		WayPoint(glm::vec3(7.4997180666451, -1.7690467585517, z)),
		WayPoint(glm::vec3(8.8874737812391, -1.856144397543, z), EndPoint),
		});

	/*5.1*/std::vector<WayPoint> waypoints10 = {
		WayPoint(glm::vec3(1.8317933679565, -5.0394228135905,z)),
		WayPoint(glm::vec3(1.6493525516954, -4.324862949901,z)),
		WayPoint(lightspos[10],TrafficPoint, "5.1"),
		WayPoint(glm::vec3(1.2655508561342, -2.2651794953588,z), SplitPoint, "-1", std::vector<WayPoints*>{splitbottomstraight51,splitbottomright51}),
		
	};

	
	paths.push_back(new WayPoints(waypoints0,"1.1"));
	paths.push_back(new WayPoints(waypoints1,"2.1"));
	paths.push_back(new WayPoints(waypoints2,"42.0"));
	paths.push_back(new WayPoints(waypoints3,"12.1"));
	paths.push_back(new WayPoints(waypoints4,"11.1"));
	paths.push_back(new WayPoints(waypoints5,"10.1"));
	paths.push_back(new WayPoints(waypoints6,"9.1"));
	paths.push_back(new WayPoints(waypoints7,"8.1"));
	paths.push_back(new WayPoints(waypoints8,"7.1"));
	paths.push_back(new WayPoints(waypoints9,"6.1"));
	paths.push_back(new WayPoints(waypoints10,"5.1"));


	//bike

	WayPoints* splitbottomlefteast = new WayPoints
	({
		WayPoint(glm::vec3(-3.1716065658536, 0.7320769193107, z)),
		WayPoint(glm::vec3(-2.771603394783, 0.5026633359026, z)),
		WayPoint(glm::vec3(-2.1480690398787, 0.114424963981, z)),
		WayPoint(glm::vec3(-1.6657122747641, -0.2796958075151, z)),
		WayPoint(glm::vec3(-1.0972404482609, -0.825638718659, z)),
		WayPoint(glm::vec3(-0.6318822333853, -1.5689015030759, z)),
		WayPoint(glm::vec3(-0.4861123584039, -2.2304724741452, z),TrafficPoint, "99.0"),// trein stoplicht
		WayPoint(glm::vec3(-0.4069809685429, -3.2807699599339, z)),
		WayPoint(glm::vec3(-0.4474318935296, -4.3324940095897, z)),
		WayPoint(glm::vec3(-0.4474318935296, -4.7673414531974, z), EndPoint),
	});

	WayPoints* splitbottomleftwest = new WayPoints
	({
		WayPoint(glm::vec3(-3.6280620229767, 1.1423242118342,z)),
		WayPoint(glm::vec3(-3.976072853295, 1.2317722135855,z)),
		WayPoint(glm::vec3(-4.5145460336825, 1.4063942620235,z)),
		WayPoint(glm::vec3(-5, 1.5,z)),
		WayPoint(glm::vec3(-5.5109123079851, 1.5989270832386,z)),
		WayPoint(glm::vec3(-6.0658491843453, 1.6742888812628,z)),
		WayPoint(glm::vec3(-6.6413392783484, 1.7359485341917,z)),
		WayPoint(glm::vec3(-7.2921911703757, 1.7565017518347,z)),
		WayPoint(glm::vec3(-7.8128726839976, 1.7565017518347,z)),
		WayPoint(glm::vec3(-8.2376391819523, 1.77020389693,z)),
		WayPoint(glm::vec3(-8.861086783789, 1.7770549694776,z), EndPoint),
		});



	WayPoints* splittopleftsouth = new WayPoints
	({
		WayPoint(glm::vec3(-2.065470863149, 3.5176804247066, z)),
		WayPoint(glm::vec3(-2.1554209614952, 3.2523276345853, z)),
		WayPoint(glm::vec3(-2.2498685647587, 3.000467359216, z)),
		WayPoint(lightspos[16], TrafficPoint, "26.1"), // stoplicht
		WayPoint(glm::vec3(-2.5587026270678, 2.1877021252659, z)),
		WayPoint(glm::vec3(-2.9746230861281, 1.2518585251281, z)),
		WayPoint(glm::vec3(-3.0958109530275, 0.957077473291,z), SplitPoint, "-1", std::vector<WayPoints*>{splitbottomlefteast,splitbottomleftwest}),
	});

	WayPoints* splittopleftnorth = new WayPoints
	({
		WayPoint(glm::vec3(-1.6, 3.8, z)),
		WayPoint(glm::vec3(-1.400323189565, 4.2560510035559, z)),
		WayPoint(glm::vec3(-1.2375001483952, 4.717382953537, z)),
		WayPoint(glm::vec3(-1.0520627959519, 5.0701662094048, z), EndPoint),
	});



	WayPoints* splittoprightwest = new WayPoints
	({
	WayPoint(glm::vec3(1.620997583112, 2.5319778394301, z)),
	WayPoint(lightspos[18], TrafficPoint, "28.1"),
	WayPoint(glm::vec3(0.7026257657899, 2.7811597497058, z)),
	WayPoint(glm::vec3(-1, 3.2, z)),
	WayPoint(glm::vec3(-1.4243749428383, 3.3045982503358, z)),
	WayPoint(glm::vec3(-1.7369176884792, 3.3977600302865, z), SplitPoint, "-1",std::vector<WayPoints*>{splittopleftnorth,splittopleftsouth})
	});



	/*std::vector<WayPoint> splittoprightnorth2 =
	{*/
	WayPoints* splittoprightnorth = new WayPoints
	({
		WayPoint(glm::vec3(2.0073804759653, 2.4268303862112,z)), //split
		WayPoint(glm::vec3(2.3203058348275, 3.2435438115671, z)),
		WayPoint(glm::vec3(2.5667800763747, 3.9231287637771, z)),
		WayPoint(glm::vec3(2.8037206037346, 4.5710885732921, z)),
		WayPoint(glm::vec3(3.0001301134159, 5.0658727922079, z), EndPoint),
	});


	/*std::vector<WayPoint> splittoprightnorth =
	{*/
	WayPoints* splittoprightnorth2 = new WayPoints
	({
		WayPoint(glm::vec3(2.0073804759653, 2.4268303862112,z), SplitPoint, "-1",std::vector<WayPoints*>{splittoprightwest,splittoprightnorth}), //split

	});



	WayPoints* splittoprighteast = new WayPoints
	({
	/*std::vector<WayPoint> splittoprighteast =
	{*/
		WayPoint(glm::vec3(1.92396216694, 1.103253546383,z)),
		WayPoint(glm::vec3(2.8760401888494, 0.834518921357,z)),
		WayPoint(glm::vec3(4.038781641347, 0.6220950021507,z)),
		WayPoint(glm::vec3(5.4215626090726, 0.3515345179165,z)),
		WayPoint(glm::vec3(6.8265891492556, 0.0936533925303,z)),
		WayPoint(glm::vec3(7.9008314469685, 0.0659310106539,z)),
		WayPoint(glm::vec3(8.8919065990519, 0.0312780333083,z), EndPoint),

	});


	std::vector<WayPoint> bikewaypoints0 = {
		WayPoint(glm::vec3(2.3649879308739, -4.964727604776, z)),
		WayPoint(glm::vec3(2.1376245552665, -4.0227936201166, z)),
		WayPoint(glm::vec3(2.0206948192398, -3.3212152039565, z), TrafficPoint, "99.0"), /*train 99.0*/
		WayPoint(glm::vec3(1.8712846009835, -2.3013280619459, z)),
		WayPoint(glm::vec3(2.3000269664146, -1.7686481533799, z)),
		WayPoint(lightspos[23],TrafficPoint, "22.0"),
		WayPoint(glm::vec3(2.0833062265068, -0.100244858336, z)),
		WayPoint(glm::vec3(1.923963216694, 1.103253546383, z), SplitPoint, "-1", std::vector<WayPoints*>{ splittoprightnorth2,splittoprighteast }),
	};

	bikepaths.push_back(new WayPoints(bikewaypoints0));

	WayPoints* splittoprighteast2 = new WayPoints
	({
		WayPoint(glm::vec3(1.7344430133265, 2.2393929296822,z)),
		WayPoint(glm::vec3(1.6525194775252, 1.8775639798928,z)),
		WayPoint(glm::vec3(1.659346438842, 1.5771776819545,z)),
		WayPoint(glm::vec3(1.720789090693, 1.2563105000659,z), SplitPoint, "-1",std::vector<WayPoints*>{ splittoprighteast,splittoprighteast }), //split
		});



	std::vector<WayPoint> bikewaypoints1 = {
		WayPoint(glm::vec3(2.8677185919119, 5.0589279535122, z)),
		WayPoint(glm::vec3(2.6560827910917, 4.6151754679215, z)),
		WayPoint(glm::vec3(2.430793067638, 3.9597871815106, z)),
		WayPoint(glm::vec3(2.2055033441843, 3.297571933783, z)),
		WayPoint(glm::vec3(1.905117046246, 2.4715096144527, z), SplitPoint, "-1", std::vector<WayPoints*>{ splittoprightwest,splittoprighteast2 }) //split
	};

	bikepaths.push_back(new WayPoints(bikewaypoints1));


	WayPoints* splittoprightnorthfromsouth = new WayPoints
	({
		WayPoint(glm::vec3(2.4413863820367, 3.196796226526, z)),
		WayPoint(glm::vec3(2.6933648161051, 3.8882719293183, z)),
		WayPoint(glm::vec3(2.8984635415096, 4.5211479962809, z)),
		WayPoint(glm::vec3(3.1094222304971, 5.0602646459156, z), EndPoint),
		});

	std::vector<WayPoint> bikewaypoints2 =
	{
		WayPoint(glm::vec3(8.8294356458248, 0.2264926653515, z)),
		WayPoint(glm::vec3(8.0334487890244, 0.2373742630185, z)),
		WayPoint(glm::vec3(6.9766043146292, 0.2745512566254, z)),
		WayPoint(glm::vec3(5.5810453488946, 0.5118478549802, z)),
		WayPoint(glm::vec3(3.9829266386036, 0.8275493468957, z)),
		WayPoint(glm::vec3(2.6151863377684, 1.083636892584, z)),
		WayPoint(glm::vec3(2.0622700459414, 1.223321008414, z)),
		WayPoint(glm::vec3(1.8873375557905, 1.5937680758903, z)),
		WayPoint(glm::vec3(1.9333394029771, 2.0537865477567, z)),
		WayPoint(glm::vec3(2.0629809723213, 2.3005237281214, z), SplitPoint, "-1", std::vector<WayPoints*>{ splittoprightwest,splittoprightnorthfromsouth }) // split
	};

	bikepaths.push_back(new WayPoints(bikewaypoints2));

	WayPoints* splittoplefttoeast = new WayPoints
	({
		WayPoint(glm::vec3(-1.7997498786026, 3.2342909368346,z)),
		WayPoint(glm::vec3(-1.4452713817529, 3.1355754060663,z)),
		WayPoint(glm::vec3(-1.1132282328051, 3.0862176406822,z), TrafficPoint, "88.1"),
		WayPoint(glm::vec3(0.6, 2.6,z)),
		WayPoint(glm::vec3(1.3475429244315, 2.4197846273787,z)),
		WayPoint(glm::vec3(1.7587163839669, 2.2812370486222,z), SplitPoint, "-1", std::vector<WayPoints*>{ splittoprighteast,splittoprightnorth }) // split
		});

	std::vector<WayPoint> bikewaypoints3 =
	{
		WayPoint(glm::vec3(-1.335556172347, 5.0681626068624, z)),
		WayPoint(glm::vec3(-1.4994133176024, 4.7188881656602, z)),
		WayPoint(glm::vec3(-1.680518583411, 4.2919971819685, z)),
		WayPoint(glm::vec3(-1.883183999911, 3.9082264996598, z)),
		WayPoint(glm::vec3(-2.1548418986239, 3.3649107022341,z), SplitPoint, "-1", std::vector<WayPoints*>{ splittoplefttoeast,splittopleftsouth }) // split
	};

	bikepaths.push_back(new WayPoints(bikewaypoints3));

	WayPoints* splitbottomlefttonorth = new WayPoints
	({
		WayPoint(lightspos[15],TrafficPoint, "86.1"),
		WayPoint(glm::vec3(-2.7468467739785, 0.9611287749123,z)),
		WayPoint(glm::vec3(-2.2839845163212, 2.1666052041956,z)),
		WayPoint(glm::vec3(-2.0155116725734, 2.7943148065189,z)),
		WayPoint(glm::vec3(-1.8, 3.2,z), SplitPoint, "-1", std::vector<WayPoints*>{ splittoplefttoeast,splittopleftnorth}) // split
		});
	WayPoints* splitbottomlefttoeast = new WayPoints
	({
		WayPoint(glm::vec3(-2.5453347301148, 0.3654626223297,z)),
		WayPoint(glm::vec3(-2.1990211019621, 0.0978566369389,z)),
		WayPoint(glm::vec3(-1.8527074738093, -0.138266291347,z)),
		WayPoint(glm::vec3(-1.4355569671707, -0.4609676266712,z)),
		WayPoint(glm::vec3(-1.16795098178, -0.7364443763382,z)),
		WayPoint(glm::vec3(-0.9003449963892, -1.1299825901481,z)),
		WayPoint(glm::vec3(-0.6878343609318, -1.6258407395487,z)),
		WayPoint(glm::vec3(-0.5697728967888, -2.0980865961206,z)),
		WayPoint(glm::vec3(-0.4831944897506, -2.4365294599972,z), TrafficPoint, "99.0"),//99
		WayPoint(glm::vec3(-0.4280991398172, -3.0110952521598,z)),
		WayPoint(glm::vec3(-0.4123576112648, -3.3810211731411,z)),
		WayPoint(glm::vec3(-0.3966160827124, -3.9555869653037,z)),
		WayPoint(glm::vec3(-0.4517114326458, -4.3569959433898,z)),
		WayPoint(glm::vec3(-0.4438406683696, -4.6088604002282,z), EndPoint),
		});

	std::vector<WayPoint> bikewaypoints4 =
	{
		WayPoint(glm::vec3(-8.8768488818595, 1.5529291064841,z)),
		WayPoint(glm::vec3(-8.3331502497011, 1.534180877789,z)),
		WayPoint(glm::vec3(-7.8331974844979, 1.5279314682239,z)),
		WayPoint(glm::vec3(-7.2457529853843, 1.5154326490939,z)),
		WayPoint(glm::vec3(-6.8020449062665, 1.4841856012687,z)),
		WayPoint(glm::vec3(-6.3458380080187, 1.4466891438784,z)),
		WayPoint(glm::vec3(-5.8021393758603, 1.4029432769231,z)),
		WayPoint(glm::vec3(-5.2396925150067, 1.3092021334476,z)),
		WayPoint(glm::vec3(-4.6210009680679, 1.1717151230167,z)),
		WayPoint(glm::vec3(-4.1085493837347, 1.0467269317159,z)),
		WayPoint(glm::vec3(-3.6023472089665, 0.8592446447648,z)),
		WayPoint(glm::vec3(-3.2273826350642, 0.734256453464,z)),
		WayPoint(glm::vec3(-2.914631778998, 0.5949303096318,z), SplitPoint, "-1", std::vector<WayPoints*>{splitbottomlefttoeast,splitbottomlefttonorth})//split
	};
	bikepaths.push_back(new WayPoints(bikewaypoints4));

	//Train
	WayPoints* splittrain1 = new WayPoints
	({
		WayPoint(glm::vec3(3.8355656098394, -2.6390335567997, z)),
		WayPoint(glm::vec3(-8.9574269985002, -2.6361722130225,z), EndPoint),
	});
	WayPoints* splittrain2 = new WayPoints
	({
		WayPoint(glm::vec3(3.8353918822043, -2.895685941053, z)),
		WayPoint(glm::vec3(-8.9574269985002, -2.9018107689424, z),EndPoint),
	});

	WayPoints* splittrain3 = new WayPoints
	({
		WayPoint(glm::vec3(5.1943877825627, -2.6458779943563,z)),
		WayPoint(glm::vec3(8.911639828274, -2.6338971541956,z), EndPoint),
		});

	std::vector<WayPoint> trainpoints1 = {
		WayPoint(glm::vec3(8.912f, -2.634f, z),TrafficPoint, "160.0"),
		WayPoint(glm::vec3(5.1943877825627, -2.6458779943563, z),SplitPoint, "-1", std::vector<WayPoints*>{ splittrain1,splittrain2 }) //split),
	};

	std::vector<WayPoint> trainpoints2 = {
		WayPoint(glm::vec3(-8.9574269985002, -2.6361722130225, z)),
		WayPoint(glm::vec3(-1.1360919527864, -2.6231885826518,z),TrafficPoint, "152.0"),//light
		WayPoint(glm::vec3(3.8355656098394, -2.6390335567997, z),SplitPoint, "-1", std::vector<WayPoints*>{ splittrain3,splittrain3 }) //split),
	};

	std::vector<WayPoint> trainpoints3 = {
		WayPoint(glm::vec3(-8.9574269985002, -2.9018107689424, z)),
		WayPoint(glm::vec3(-1.1312054528269, -2.8919460804226,z), TrafficPoint, "154.0"), //light
		WayPoint(glm::vec3(3.8353918822043, -2.895685941053, z),SplitPoint, "-1", std::vector<WayPoints*>{ splittrain3,splittrain3 }) //split),
	};

	trainpaths.push_back(new WayPoints(trainpoints1, "160.0"));
	trainpaths.push_back(new WayPoints(trainpoints2, "152.0"));
	trainpaths.push_back(new WayPoints(trainpoints3, "154.0"));


	//People

	WayPoints* toprighttoeast = new WayPoints
	({
		WayPoint(glm::vec3(2.6451785512691, 1.2406286614797,z)),
		WayPoint(glm::vec3(3.0775762781699, 1.1142354797702,z)),
		WayPoint(glm::vec3(3.5, 1,z)),
		WayPoint(glm::vec3(3.9623285501362, 0.9279718435668,z)),
		WayPoint(glm::vec3(4.3614649134293, 0.8614491163512,z)),
		WayPoint(glm::vec3(4.8736899129887, 0.7749695709711,z)),
		WayPoint(glm::vec3(5.3060876398896, 0.6884900255909,z)),
		WayPoint(glm::vec3(5.8515740030568, 0.6153150256538,z)),
		WayPoint(glm::vec3(6.5, 0.5,z)),
		WayPoint(glm::vec3(7.2203561023785, 0.4305926253325,z)),
		WayPoint(glm::vec3(7.8919214631834, 0.4229612007779,z)),
		WayPoint(glm::vec3(8.7542724378532, 0.3924355025595,z), EndPoint) //endpoint
		});

	WayPoints* toprighttonorth= new WayPoints
	({
		WayPoint(glm::vec3(2.5463013475776, 2.9031647490581,z)),
		WayPoint(glm::vec3(2.6764660935343, 3.2213452391745,z)),
		WayPoint(glm::vec3(2.7849367151649, 3.5901453527186,z)),
		WayPoint(glm::vec3(2.8717132124694, 3.850474844632,z)),
		WayPoint(glm::vec3(3.0235720827523, 4.19758083385,z)),
		WayPoint(glm::vec3(3.1175799548321, 4.4868358248649,z)),
		WayPoint(glm::vec3(3.2405133260135, 4.739933942003,z)),
		WayPoint(glm::vec3(3.3489839476441, 5.0147261834672,z), EndPoint) //endpoint
	});

	WayPoints* toplefttowest = new WayPoints
	({
		WayPoint(glm::vec3(-2.6221693117707, 4.012930654528,z)),
		WayPoint(glm::vec3(-3.2465764941627, 4.1934821289546,z)),
		WayPoint(glm::vec3(-3.9236445232624, 4.494401252999,z)),
		WayPoint(glm::vec3(-4.40746353865, 4.2523301709496,z)),
		WayPoint(glm::vec3(-5.1597633263957, 3.9071573271604,z)),
		WayPoint(glm::vec3(-6, 3.5,z)),
		WayPoint(glm::vec3(-6.6378111446728, 3.3584210113928,z)),
		WayPoint(glm::vec3(-7.4963179612768, 3.2610645682728,z)),
		WayPoint(glm::vec3(-8.1512613059025, 3.1991104681055,z)),
		WayPoint(glm::vec3(-8.7088482074082, 3.1548575394145,z), EndPoint), // endpoint
		});

	WayPoints* bottomlefttowest = new WayPoints
	({
		WayPoint(glm::vec3(-4.5, 1,z)),
		WayPoint(glm::vec3(-5.3396072285957, 1.2273769773524,z)),
		WayPoint(glm::vec3(-6.0919070163415, 1.351285177687,z)),
		WayPoint(glm::vec3(-6.737999775229, 1.4309404493307,z)),
		WayPoint(glm::vec3(-7.4371960485457, 1.4132392778543,z)),
		WayPoint(glm::vec3(-7.977081778575, 1.4220898635925,z)),
		WayPoint(glm::vec3(-8.7811871730407, 1.4143159179602,z), EndPoint)//endpoint
		});
	WayPoints* bottomlefttosouth = new WayPoints
	({
		WayPoint(glm::vec3(-3.8527088245805, 0.3777207464865,z)),
		WayPoint(glm::vec3(-3.3570760232421, 0.06795024565,z)),
		WayPoint(glm::vec3(-2.8525926361655, -0.312624941092,z)),
		WayPoint(glm::vec3(-2.3392586633507, -0.7640048137395,z)),
		WayPoint(glm::vec3(-1.8440742339069, -1.1892315073996,z)),
		WayPoint(glm::vec3(-1.4000195338177, -1.4016054943987,z)),
		WayPoint(glm::vec3(-0.9849249228648, -1.6236328444433,z)),
		WayPoint(glm::vec3(-0.7242841206386, -2.4248619772129,z),TrafficPoint, "99.0"), // train
		WayPoint(glm::vec3(-0.6866864211402, -3.1915969828072,z)),
		WayPoint(glm::vec3(-0.6640549808297, -3.6781729494831,z)),
		WayPoint(glm::vec3(-0.6753707009849, -4.1760646363142,z)),
		WayPoint(glm::vec3(-0.7319493017612, -4.8210606851636,z), EndPoint) // endpoint
		});

	WayPoints* toplefttosouth = new WayPoints
	({
		WayPoint(glm::vec3(-2.2507528059689, 3.5816327837099,z)),
		WayPoint(glm::vec3(-2.4277645207326, 3.2453105256588,z)),
		WayPoint(glm::vec3(-2.640178578449, 2.8912870961314,z),TrafficPoint, "35.2"),//35.2
		WayPoint(glm::vec3(-2.9056961505946, 2.3248496088875,z),TrafficPoint, "35.1"), //35.1
		WayPoint(glm::vec3(-3.3305242660275, 1.3247334204724,z)),
		WayPoint(glm::vec3(-3.6579959383404, 0.7671465189667,z),SplitPoint, "-1", std::vector<WayPoints*>{ bottomlefttosouth, bottomlefttowest }) //split),
	});

	WayPoints* toprighttowest = new WayPoints
	({
		WayPoint(glm::vec3(1.881750717407, 2.8108690910822,z)),
		WayPoint(glm::vec3(1.4983332690392, 2.926357444198,z),TrafficPoint, "37.1"),//37.1
		WayPoint(glm::vec3(0.7805903968596, 3.11565226763,z),TrafficPoint, "37.2"), //37.2
		WayPoint(glm::vec3(-0.9230630140283, 3.5336783360423,z)),
		WayPoint(glm::vec3(-1.4278492098469, 3.6756494536163,z)),
		WayPoint(glm::vec3(-2.0982683761685, 3.8886061299773,z),SplitPoint, "-1", std::vector<WayPoints*>{toplefttowest,toplefttosouth  }) //split),
		});
	WayPoints* toprighttocornernorth = new WayPoints
	({
		WayPoint(glm::vec3(2.1124188610552, 1.4279642948818,z)),
		WayPoint(glm::vec3(2.1485757349321, 1.7533761597736,z)),
		WayPoint(glm::vec3(2.2787404808888, 2.1077135237669,z)),
		WayPoint(glm::vec3(2.4305993511716, 2.5994470084924,z),SplitPoint, "-1", std::vector<WayPoints*>{ splittoprightnorth,toprighttowest }) //split),
		});

	std::vector<WayPoint> peoplepoints1 = {
		WayPoint(glm::vec3(2.7418969827878, -4.8395260061285,z)),
		WayPoint(glm::vec3(2.5054832670782, -3.8481136499268,z)),
		WayPoint(glm::vec3(2.3605845380949, -3.0854887605409,z),TrafficPoint, "99.0"),//train
		WayPoint(glm::vec3(2.246190804687, -2.4143788578813,z)),
		WayPoint(glm::vec3(2.2080595602177, -2.2313488844287,z)),
		WayPoint(glm::vec3(2.7876544761509, -2.1474601465962,z)),
		WayPoint(glm::vec3(2.6580082449554, -1.3772090083165,z),TrafficPoint, "31.1"),// 31.1 light
		WayPoint(glm::vec3(2.4943044325692, -0.2473785574872,z),TrafficPoint, "31.2"),// 31.2 light
		WayPoint(glm::vec3(2.3789341253456, 0.8355958597243,z)),
		WayPoint(glm::vec3(2.3596560094596, 1.298270640989,z),SplitPoint, "-1", std::vector<WayPoints*>{toprighttoeast,toprighttocornernorth }) //split),
	};

	peoplepaths.push_back(new WayPoints(peoplepoints1));

	WayPoints* toprighttosouth = new WayPoints
	({
		WayPoint(glm::vec3(2.2115913541797, 1.3061836475125,z)),
		WayPoint(glm::vec3(2.1575381236839, 0.8928457113039,z),TrafficPoint, "32.2"), //light
		WayPoint(glm::vec3(2.2761002758497, -0.1849920356579,z),TrafficPoint, "32.1"), //light
		WayPoint(glm::vec3(2.4433737302555, -1.37317197741,z)),
		WayPoint(glm::vec3(2.5, -2,z)),
		WayPoint(glm::vec3(2.0440456464232, -2.2658062849006,z)),
		WayPoint(glm::vec3(2.075181303763, -2.4551027241758,z),TrafficPoint, "99.0"), // train
		WayPoint(glm::vec3(2.1952978153367, -3.1173151600968,z)),
		WayPoint(glm::vec3(2.3036887014487, -3.896374654027,z)),
		WayPoint(glm::vec3(2.4648838678413, -4.8042798643265,z), EndPoint), //endpoint
		});

	std::vector<WayPoint> peoplepoints2 = {
		WayPoint(glm::vec3(8.759156070575, 0.5203238548728,z)),
		WayPoint(glm::vec3(7.2228062945483, 0.6739588324755,z)),
		WayPoint(glm::vec3(5.349172647521, 0.8834560849757,z)),
		WayPoint(glm::vec3(3.9902977909492, 1.0734589160277,z)),
		WayPoint(glm::vec3(2.7567359749865, 1.3915201508056,z)),
		WayPoint(glm::vec3(2.4429728650029, 1.4731845218972,z),SplitPoint, "-1", std::vector<WayPoints*>{toprighttosouth,toprighttocornernorth }) //split),
	};
	peoplepaths.push_back(new WayPoints(peoplepoints2));

	WayPoints* toprighttocornersouth = new WayPoints
	({
		WayPoint(glm::vec3(2.1629669438807, 2.2885385082662,z)),
		WayPoint(glm::vec3(2, 1.8,z)),
		WayPoint(glm::vec3(2.0544721867706, 1.4729572306799,z),SplitPoint, "-1", std::vector<WayPoints*>{toprighttosouth,toprighttoeast }) //split),
		});

	WayPoints* toplefttoeast = new WayPoints
	({
		WayPoint(glm::vec3(-1.5, 3.5,z)),
		WayPoint(glm::vec3(-0.9263954309007, 3.3262480931415,z),TrafficPoint, "38.1"),//light
		WayPoint(glm::vec3(0.6562266707908, 2.9723070480347,z),TrafficPoint, "38.2"),//light
		WayPoint(glm::vec3(1.4601784732475, 2.7498298196819,z)),
		WayPoint(glm::vec3(1.8451909070985, 2.6211374672976,z)),
		WayPoint(glm::vec3(2.3393108432789, 2.4951853267026,z),SplitPoint, "-1", std::vector<WayPoints*>{toprighttonorth,toprighttocornersouth }) //split),
		});


	std::vector<WayPoint> peoplepoints3 = {
		WayPoint(glm::vec3(-1.7862979567653, 5.0350242887124,z)),
		WayPoint(glm::vec3(-1.9145183378619, 4.7999535900353,z)),
		WayPoint(glm::vec3(-2.0053411078053, 4.5702254072373,z)),
		WayPoint(glm::vec3(-2.1335614889019, 4.303099613286,z)),
		WayPoint(glm::vec3(-2.0908213618697, 4.0306313034558,z),SplitPoint, "-1", std::vector<WayPoints*>{toplefttosouth,toplefttoeast }) //split),
	};
	peoplepaths.push_back(new WayPoints(peoplepoints3));

	WayPoints* toplefttonorth = new WayPoints
	({
		WayPoint(glm::vec3(-1.9306859779261, 4.2373020592459,z)),
		WayPoint(glm::vec3(-1.7150797324435, 4.6543764357533,z)),
		WayPoint(glm::vec3(-1.5312842444911, 5.0431745833449,z), EndPoint),
		});

	WayPoints* bottomlefttonorth = new WayPoints
	({
		WayPoint(glm::vec3(-3.2029471124321, 1.2401060290095,z),TrafficPoint, "36.1"),//light
		WayPoint(glm::vec3(-2.723642279673, 2.272801748091,z),TrafficPoint, "36.2"),//light
		WayPoint(glm::vec3(- 2.4716559842217, 2.8421126519267,z)),
		WayPoint(glm::vec3(-2.16274325621, 3.5545871384272,z),SplitPoint, "-1", std::vector<WayPoints*>{toplefttoeast,toplefttonorth }) //split),
	});

	std::vector<WayPoint> peoplepoints4 = {
		WayPoint(glm::vec3(-8.8203252419819, 1.3059735181173,z)),
		WayPoint(glm::vec3(-6.8676510107157, 1.2900981178631,z)),
		WayPoint(glm::vec3(-5.3508305073442, 1.0277609658886,z)),
		WayPoint(glm::vec3(-4, 0.5,z),SplitPoint, "-1", std::vector<WayPoints*>{ bottomlefttonorth, bottomlefttosouth}) //split),
	};
	peoplepaths.push_back(new WayPoints(peoplepoints4));
}

// Todo: use inheritance from gameObject class instead of its own vector
void application::addTrafficLight(std::string id, int index, int weight, int status)
{
	lights.push_back(TrafficLight{id, index, weight, status});
}


void application::updateLightWeights()
{

};

void application::addWeight(std::string id)
{
	int index = getLightIndex(lights, id);
	if (index != -1)
	{
		lights[index].weight++;
	}

};

void application::removeWeight(std::string id)
{
	int index = getLightIndex(lights, id);
	if (index != -1)
	{
		lights[index].weight--;
	}

};