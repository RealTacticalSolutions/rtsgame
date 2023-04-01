#include "pch.h"
#include "application.h"
#include "CROSSROAD/pchroads.h"
#include "color.h"
#include "CROSSROAD/crossroadlevel.h"


void application::mainLoop()
{

	CrossRoadLevel level(message, scene.gameObjects, lights);

	level.init();
	

	double lastFrameTime = glfwGetTime();
	double lastSecondTime = lastFrameTime;
	int fps = 0;
	char windowTitle[256];
	Input input = Input(windowObject.get()->getWindow());

	while (!windowObject->shouldClose())
	{
		double currentFrameTime = glfwGetTime();
		double delta = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		//updateColorAddition(0, glm::vec3(0.0001f, 0.0001f, 0.0001f));
		glfwPollEvents();

		level.mainLoop();
		updateTest();
		updateWayPoints();
		drawFrame();

		glm::vec2 cursorPos = input.getCursorPos();
		bool spacePressed = input.keyPressed(GLFW_KEY_SPACE);
		bool test = input.keyDown(GLFW_KEY_SPACE);

		input.updateInput();

		if (test) {
			scene.removeObject(0);
			int width = 0, height = 0;

			glfwGetFramebufferSize(windowObject.get()->getWindow(), &width, &height);
			glm::vec3 worldpos = GameMath::windowToWorldPos(cursorPos, glm::vec2(width, height), camera);
			// std::cout << "cursor X: " << cursorPos.x << "  cursor Y: " << cursorPos.y << std::endl;
			 //std::cout << "world X: " << worldpos.x << "  world Y: " << worldpos.y << "  world Z: " << worldpos.z << std::endl;
			 //scene.addObject();
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

	scene.blueprintObject(ShapeTool::createSquare(0.5f), "../../../textures/kruispunt2.png");

	scene.blueprintObject(ShapeTool::createSquare(0.07f), "../../../textures/light.jpg");

	scene.blueprintObject(ShapeTool::createSquare(0.05f), "../../../textures/car.jpg");

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
	camera.setPosition(glm::vec3(0.0f, 0.0f, 4.0f));
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

	spawnpoint = paths[0].getWayPointPosition(0);
	scene.instantiateCar(scene.bluePrints[2], glm::translate(glm::mat4(1.0f), spawnpoint), glm::vec3(1.0f, 1.0f, 1.0f), paths[0]);

	spawnpoint = glm::vec3(1.5f, 0.18f, 1.0f);
	scene.instantiateCar(scene.bluePrints[2], glm::translate(glm::mat4(1.0f), spawnpoint), glm::vec3(1.0f, 0.0f, 1.0f), paths[0]);

	////spawnpoint = paths[1].getWayPointPosition(0);
	//spawnpoint = glm::vec3(1.0f, 0.0f, 1.0f);
	//scene.instantiateObject(scene.bluePrints[2], glm::translate(glm::mat4(1.0f), spawnpoint), glm::vec3(1.0f, 1.0f, 1.0f));
	//cars.push_back(car{ static_cast<int>(scene.gameObjects.size() - 1), 0, paths[1] });

}

void application::cleanup()
{
}

void application::updateTest()
{
	//// Check for intersection with another object
	//if ((Intersection::intersectSquares(gameObjects[5], gameObjects[1])) && gameObjects[1].properties.color == getColor(RED)) 
	//{
	//    return; // Don't update if there's an intersection
	//}

	//int testindex = 2;
	//// Set the target position
	//glm::vec3 target(-0.1f, -1.2f, 1.0f);

	//// Get the current position of the object
	//glm::vec3 position = glm::vec3(scene.gameObjects[testindex].properties.transform[3]);

	//// Calculate the direction from the current position to the target position
	//glm::vec3 direction = glm::normalize(target - position);

	//// Set the velocity
	//float velocity = 0.00005f;

	//// Calculate the new position based on the direction and velocity
	//glm::vec3 new_pos = position + direction * velocity;

	//if (approxEqual(position, target, 0.15f))
	//{
	//    scene.gameObjects[testindex].properties.transform = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,1.0f,1.0f));
	//}
	//else
	//{ 
	//// Update the position of the object using glm::translate
	//scene.gameObjects[testindex].properties.transform = glm::translate(glm::mat4(1.0f), new_pos);
	//}

}


bool application::approxEqual(glm::vec3 a, glm::vec3 b, float epsilon)
{
	return glm::all(glm::lessThanEqual(glm::abs(a - b), glm::vec3(epsilon)));
}

void application::updateWayPoints()
{
	if (scene.gameObjects.empty())
	{
		return;
	}

	std::vector<std::pair<size_t, Car*>> cars;
	for (size_t i = 0; i < scene.gameObjects.size(); i++)
	{
		if (Car* car = dynamic_cast<Car*>(scene.gameObjects[i].get())) {
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
		WayPoints waypoints = car->getWayPoints();
		glm::vec3 target(waypoints.getWayPointPosition(currentpoint));	

		// Get the current position of the object
		glm::vec3 position = glm::vec3(car->properties.transform[3]);

		// Calculate the direction from the current position to the target position
		glm::vec3 direction = glm::normalize(target - position);

		// Set the velocity
		float velocity = 0.00005f;

		// Calculate the new position based on the direction and velocity
		glm::vec3 new_pos = position + direction * velocity;

		if (approxEqual(position, target, 0.05f))
		{
			std::string lightid = waypoints.getLightId(currentpoint);
			if (!( lightid == "-1"))
			{
				if (scene.gameObjects[getId(lights,lightid)]->properties.color == getColor(RED))
				{
					continue;
				}
			}
			int nextwaypoint = currentpoint + 1;
			if (nextwaypoint > waypoints.getSize() - 1)
			{
				// Todo: destruct object probably
				//scene.removeObject(index);
				carstoremove.push_back(index);
				continue;
			}
			car->setCurrentWayPoint(nextwaypoint);
			//scene.gameObjects[index].properties.transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 1.0f));
		}
		else
		{
			// Update the position of the object using glm::translate
			scene.gameObjects[index]->properties.transform = glm::translate(glm::mat4(1.0f), new_pos);
		}
		
	}
	for (size_t i = 0; i < carstoremove.size(); i++)
	{
		scene.removeObject(carstoremove[i]);
	}
}

void application::initWayPoints()
{	
	/*1.1*/std::vector<WayPoint> waypoints0 = { WayPoint(glm::vec3(1.0f, 0.18f, 1.0f)),WayPoint(lightspos[0],"1.1"),WayPoint(glm::vec3(-0.3f,0.3f,1.0f)),WayPoint(glm::vec3(-1.2f,0.3f,1.0f)) };
	/*2.1*/std::vector<WayPoint> waypoints1 = { WayPoint(glm::vec3(1.0f, 0.0f, 1.0f)),WayPoint(lightspos[1],"2.1"),WayPoint(glm::vec3(0.0f,0.0f,1.0f)),WayPoint(glm::vec3(-0.3f,0.3f,1.0f)),WayPoint(glm::vec3(-1.2f,0.3f,1.0f)) };
	/*42.0*/std::vector<WayPoint> waypoints2 = { WayPoint(glm::vec3(1.2f, 0.35f, 1.0f)),WayPoint(lightspos[2],"42.0"),WayPoint(glm::vec3(-1.2f,0.35f,1.0f)) };
	/*12.1*/std::vector<WayPoint> waypoints3 = { WayPoint(glm::vec3(0.1f, 1.20f, 1.0f)),WayPoint(lightspos[3],"12.1"),WayPoint(glm::vec3(0.1f,-0.20f,1.0f)),WayPoint(glm::vec3(0.3f,-0.20f,1.0f)),WayPoint(glm::vec3(1.2f,-0.20f,1.0f)) };
	/*11.1*/std::vector<WayPoint> waypoints4 = { WayPoint(glm::vec3(-0.18f, 1.20f, 1.0f)),WayPoint(lightspos[4],"11.1"),WayPoint(glm::vec3(-0.18f,-1.20f,1.0f)) };
	/*10.1*/std::vector<WayPoint> waypoints5 = { WayPoint(glm::vec3(-0.38f, 1.20f, 1.0f)),WayPoint(lightspos[5],"10.1"),WayPoint(glm::vec3(-0.38f,0.30f,1.0f)),WayPoint(glm::vec3(-1.2f,0.38f,1.0f)) };
	/*9.1*/std::vector<WayPoint> waypoints6 = { WayPoint(glm::vec3(-1.2f, 0.0f, 1.0f)),WayPoint(lightspos[6],"9.1"),WayPoint(glm::vec3(0.0f,0.0f,1.0f)),WayPoint(glm::vec3(0.3f,-0.2f,1.0f)),WayPoint(glm::vec3(1.2f,-0.2f,1.0f)) };
	/*8.1*/std::vector<WayPoint> waypoints7 = { WayPoint(glm::vec3(-1.2f, -0.20f, 1.0f)),WayPoint(lightspos[7],"8.1"),WayPoint(glm::vec3(1.2f,-0.20f,1.0f)) };
	/*7.1*/std::vector<WayPoint> waypoints8 = { WayPoint(glm::vec3(-1.2f, -0.40f, 1.0f)),WayPoint(lightspos[8],"7.1"),WayPoint(glm::vec3(-0.32f,-0.40f,1.0f)),WayPoint(glm::vec3(-0.32f,-1.2f,1.0f)) };
	/*6.1*/std::vector<WayPoint> waypoints9 = { WayPoint(glm::vec3(0.16f, -1.2f, 1.0f)),WayPoint(lightspos[9],"6.1"),WayPoint(glm::vec3(0.16f,0.35f,1.0f)),WayPoint(glm::vec3(-1.2f,0.35f,1.0f)) };
	/*5.1*/std::vector<WayPoint> waypoints10 = {WayPoint(glm::vec3(0.34f, -0.60f, 1.0f)),WayPoint(lightspos[10],"5.1"),WayPoint(glm::vec3(0.34f, 1.0f, 1.0f)),WayPoint(glm::vec3(0.34f, 1.2f, 1.0f))};
	paths.push_back(waypoints0);
	paths.push_back(waypoints1);
	paths.push_back(waypoints2);
	paths.push_back(waypoints3);
	paths.push_back(waypoints4);
	paths.push_back(waypoints5);
	paths.push_back(waypoints6);
	paths.push_back(waypoints7);
	paths.push_back(waypoints8);
	paths.push_back(waypoints9);
	paths.push_back(waypoints10);
}

// Todo: use inheritance from gameObject class instead of its own vector
void application::addTrafficLight(std::string id, int index, double weight, int status)
{
	lights.push_back(TrafficLight{id, index, weight, status});
}
