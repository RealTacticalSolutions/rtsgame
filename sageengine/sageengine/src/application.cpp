#include "pch.h"
#include "application.h"
#include "CROSSROAD/pchroads.h"
#include "color.h"
#include "CROSSROAD/crossroadlevel.h"

#include <random>
static double lastSpawnTime = 0.0;
const int maxinstances = 30;
static int carcount = 2;
static int bikecount = 0;

std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator

std::uniform_int_distribution<> dicar(0, 11); // define the range
std::uniform_int_distribution<> dibike(0, 1); // define the range
std::uniform_int_distribution<> displit(0, 1); // define the range

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
		updateTest(currentFrameTime);
		updateWayPoints(delta);
		updateWayPointsBikes(delta);
		updateLightWeights();
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

	scene.blueprintObject(ShapeTool::createRectangle(3.2f, 1.8f), "../../../textures/kruispunt.png");

	scene.blueprintObject(ShapeTool::createSquare(0.07f), "../../../textures/light.jpg");

	scene.blueprintObject(ShapeTool::createSquare(0.05f), "../../../textures/car.jpg");

	scene.blueprintObject(ShapeTool::createSquare(0.05f), "../../../textures/bike.jpg");

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

	scene.instantiateObject(scene.bluePrints[1], glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,2.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	////spawnpoint = paths[1].getWayPointPosition(0);
	//spawnpoint = glm::vec3(1.0f, 0.0f, 1.0f);
	//scene.instantiateObject(scene.bluePrints[2], glm::translate(glm::mat4(1.0f), spawnpoint), glm::vec3(1.0f, 1.0f, 1.0f));
	//cars.push_back(car{ static_cast<int>(scene.gameObjects.size() - 1), 0, paths[1] });

}

void application::cleanup()
{
}

void application::updateTest(const double currentFrameTime)
{
	if (carcount < maxinstances && 0.1 < (currentFrameTime - lastSpawnTime))
	{
		int pathindex = dicar(gen);
		spawnpoint = paths[pathindex]->getWayPointPosition(0);
		addWeight(paths[pathindex]->getTrafficLightId());
		scene.instantiateCar(scene.bluePrints[2], glm::translate(glm::mat4(1.0f), spawnpoint), glm::vec3(1.0f, 1.0f, 0.0f), paths[pathindex]);
		lastSpawnTime = currentFrameTime;
		carcount += 1;
	}

	if (bikecount < 5 && 0.1 < (currentFrameTime - lastSpawnTime))
	{
		int pathindex = dibike(gen);
		//pathindex = 1;
		spawnpoint = bikepaths[pathindex]->getWayPointPosition(0);
		scene.instantiateBike(scene.bluePrints[3], glm::translate(glm::mat4(1.0f), spawnpoint), glm::vec3(1.0f, 1.0f, 0.0f), bikepaths[pathindex]);
		lastSpawnTime = currentFrameTime;
		bikecount += 1;
	}


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


		glm::vec3 target(waypoints->getWayPointPosition(currentpoint));

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
		float velocity = 50.0f * (delta / 60);

		// Calculate the new position based on the direction and velocity
		glm::vec3 new_pos = position + direction * velocity;


		bool removed = false;
		if (approxEqual(position, target, 0.00005f))
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
				//todo:: also remove from weight
				lightid = waypoints->getLightId(currentpoint);
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
			scene.gameObjects[index]->properties.transform = glm::translate(glm::mat4(1.0f), new_pos);
		}
	}

	for (size_t i = 0; i < carstoremove.size(); i++)
	{
		scene.removeObject(carstoremove[i]);
		carcount -= 1;
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


		glm::vec3 target(waypoints->getWayPointPosition(currentpoint));

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
		float velocity = 50.0f * (delta / 60);

		// Calculate the new position based on the direction and velocity
		glm::vec3 new_pos = position + direction * velocity;
		

		bool removed = false;
		if (approxEqual(position, target, 0.00005f))
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
				//todo:: also remove from weight
				lightid = waypoints->getLightId(currentpoint);
				if (!(lightid == "-1"))
				{
					if (scene.gameObjects[getId(lights, lightid)]->properties.color == getColor(RED))
					{
						continue;
					}
					else
					{
						bike->setCurrentWayPoint(currentpoint + 1);
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
	/*1.1*/std::vector<WayPoint> waypoints0 = { 
		WayPoint(glm::vec3(8.900f, -0.700f, 1.0f)),
		WayPoint(glm::vec3(7.4478754277318, -0.6424615826693, 1.0f)),
		WayPoint(glm::vec3(6.2655008610581, -0.5189857576686, 1.0f)),
		WayPoint(glm::vec3(5.2365356527187, -0.3543513243343, 1.0f)),
		WayPoint(lightspos[0], TrafficPoint,"1.1"),
		WayPoint(glm::vec3(3.3427633065728, 0.1018627834836, 1.0f)),
		WayPoint(glm::vec3(2.1123779288658, 0.4602762711748, 1.0f)),
		WayPoint(glm::vec3(1.3160580937782, 0.8873932736309, 1.0f)),
		WayPoint(glm::vec3(0.8756129718504, 1.2858154516885, 1.0f)),
		WayPoint(glm::vec3(0.7087367039929, 1.7901965769456, 1.0f)),
		WayPoint(glm::vec3(0.8421507086444, 2.3470550311434, 1.0f)),
		WayPoint(glm::vec3(1.0625738467643, 2.9561189654222, 1.0f)),
		WayPoint(glm::vec3(1.2249908959054, 3.5361798552115, 1.0f)),
		WayPoint(glm::vec3(1.3874079450464, 4.0524340471241, 1.0f)),
		WayPoint(glm::vec3(1.5, 4.5, 1.0f)),
		WayPoint(glm::vec3(1.6476071514173, 4.9148711321509, 1.0f), EndPoint),
		};

	/*2.2*/std::vector<WayPoint> waypoints1 = {
		WayPoint(glm::vec3(8.8884344127193, -1.0405179236746,1.0f)),
		WayPoint(glm::vec3(7.4326575402666, -0.9775453872072,1.0f)),
		WayPoint(glm::vec3(6.2224943088012, -0.8660220713649,1.0f)),
		WayPoint(glm::vec3(5.1626464011562, -0.6761999051331,1.0f)),
		WayPoint(glm::vec3(4.0004148395579, -0.451847328123,1.0f)),
		WayPoint(glm::vec3(3.2612318668167, -0.2322161308921,1.0f)),
		WayPoint(lightspos[1], TrafficPoint,"2.1"),
		WayPoint(glm::vec3(2.1452134152702, 0.1408750779783,1.0f)),
		WayPoint(glm::vec3(1.1848670970973, 0.5360175734766,1.0f)),
		WayPoint(glm::vec3(0.4716218013583, 0.9954568477721,1.0f)),
		WayPoint(glm::vec3(-0.1702132612523, 1.4263391275666,1.0f)),
		WayPoint(glm::vec3(-0.861420251756, 1.9021049781731,1.0f)),
		WayPoint(glm::vec3(-1.7612950821041, 2.2980994907728,1.0f)),
		WayPoint(glm::vec3(-2.9670375511151, 2.6695367442597,1.0f)),
		WayPoint(glm::vec3(-3.9996644447838, 2.9172218813602,1.0f)),
		WayPoint(glm::vec3(-5.2610950837471, 2.9975677819311,1.0f)),
		WayPoint(glm::vec3(-6.2734534309406, 2.9413256515315,1.0f)),
		WayPoint(glm::vec3(-7.1652929272777, 2.8690143410177,1.0f)),
		WayPoint(glm::vec3(-7.9767865230439, 2.8368759807893,1.0f)),
		WayPoint(glm::vec3(-8.6539814206188, 2.7802355590692,1.0f), EndPoint),
	};

	/*42.0*/std::vector<WayPoint> waypoints2 = {
		WayPoint(glm::vec3(8.9319992123494, -0.3680709702589, 1.0f)),
		WayPoint(glm::vec3(7.4912544025147, -0.3045805210119, 1.0f)),
		WayPoint(glm::vec3(6.3484263160696, -0.2069029067858, 1.0f)),
		WayPoint(glm::vec3(5.318416914837, -0.010425862561, 1.0f)),
		WayPoint(lightspos[2],TrafficPoint, "42.0"),
		WayPoint(glm::vec3(3.3919943110171, 0.3643813307881, 1.0f)),
		WayPoint(glm::vec3(2.7219530917216, 0.5014352165531, 1.0f)),
		WayPoint(glm::vec3(2.0444515233664, 0.656908353773, 1.0f)),
		WayPoint(glm::vec3(1.2987120313702, 0.8011683918534, 1.0f)),
		WayPoint(glm::vec3(0.4716218013583, 0.9954568477721, 1.0f)),
		WayPoint(glm::vec3(-0.1702132612523, 1.4263391275666, 1.0f)),
		WayPoint(glm::vec3(-0.861420251756, 1.9021049781731, 1.0f)),
		WayPoint(glm::vec3(-1.7612950821041, 2.2980994907728, 1.0f)),
		WayPoint(glm::vec3(-2.9670375511151, 2.6695367442597, 1.0f)),
		WayPoint(glm::vec3(-3.9996644447838, 2.9172218813602, 1.0f)),
		WayPoint(glm::vec3(-5.2610950837471, 2.9975677819311, 1.0f)),
		WayPoint(glm::vec3(-6.2734534309406, 2.9413256515315, 1.0f)),
		WayPoint(glm::vec3(-7.1652929272777, 2.8690143410177, 1.0f)),
		WayPoint(glm::vec3(-7.9767865230439, 2.8368759807893, 1.0f)),
		WayPoint(glm::vec3(-8.6539814206188, 2.7802355590692, 1.0f), EndPoint),
	};

	/*12.1*/std::vector<WayPoint> waypoints3 = {
		WayPoint(glm::vec3(0.8050734055799, 5.1258486936268, 1.0f)),
		WayPoint(glm::vec3(0.6828668579084, 4.8167380142225, 1.0f)),
		WayPoint(glm::vec3(0.5678489306882, 4.5004387143669, 1.0f)),
		WayPoint(glm::vec3(0.4456423830168, 4.1841394145114, 1.0f)),
		WayPoint(glm::vec3(0.3521903171504, 3.8534628737533, 1.0f)),
		WayPoint(lightspos[3],TrafficPoint, "12.1"),
		WayPoint(glm::vec3(0.0071365354898, 2.8398673901253, 1.0f)),
		WayPoint(glm::vec3(-0.1725789757918, 2.121005344999, 1.0f)),
		WayPoint(glm::vec3(-0.1006927712792, 0.9995805546021, 1.0f)),
		WayPoint(glm::vec3(0.5, 0.5, 1.0f)),
		WayPoint(glm::vec3(1.5167468302549, -0.1577873380512, 1.0f)),
		WayPoint(glm::vec3(2.8969619568972, -0.6250476673833, 1.0f)),
		WayPoint(glm::vec3(3.9150145814307, -0.9485812186457, 1.0f)),
		WayPoint(glm::vec3(5.0717994586123, -1.1533795633564, 1.0f)),
		WayPoint(glm::vec3(6.2216386423922, -1.3319260204651, 1.0f)),
		WayPoint(glm::vec3(7.5000312752903, -1.431912036446, 1.0f)),
		WayPoint(glm::vec3(8.9053226669936, -1.5835048929068, 1.0f), EndPoint),
	};

	/*11.1*/std::vector<WayPoint> waypoints4 = {
		WayPoint(glm::vec3(0.4669236053687, 5.1642258616477, 1.0f)),
		WayPoint(glm::vec3(0.2344505862627, 4.6262168745737, 1.0f)),
		WayPoint(glm::vec3(0, 4, 1.0f)),
		WayPoint(lightspos[4],TrafficPoint, "11.1"),
		WayPoint(glm::vec3(-0.3984978107211, 2.7101986259739, 1.0f)),
		WayPoint(glm::vec3(-0.496179609616, 2.371185323927, 1.0f)),
		WayPoint(glm::vec3(-0.5996073966811, 1.790840518728, 1.0f)),
		WayPoint(glm::vec3(-0.5847540684125, 1.2537304455903, 1.0f)),
		WayPoint(glm::vec3(-0.411610035793, 0.2086450894768, 1.0f)),
		WayPoint(glm::vec3(-0.1365356998153, -0.4790407504676, 1.0f)),
		WayPoint(glm::vec3(0.1179080609641, -1.2286183160069, 1.0f)),
		WayPoint(glm::vec3(0.2829526625507, -1.8956735807528, 1.0f)),/* stoplicht alarm trein*/
		WayPoint(glm::vec3(0.4891385172183, -3.2306959961184, 1.0f)),
		WayPoint(glm::vec3(0.5995569026235, -4.136126756441, 1.0f)),
		WayPoint(glm::vec3(0.6731691595603, -4.8354431973405, 1.0f), EndPoint),
	};

	/*10.1*/std::vector<WayPoint> waypoints5 = {
		WayPoint(glm::vec3(-0.0253063308747, 5.1897813612963, 1.0f)),
		WayPoint(glm::vec3(-0.1649131931962, 4.6871966569388, 1.0f)),
		WayPoint(glm::vec3(-0.3254610848659, 4.247435040626, 1.0f)),
		WayPoint(lightspos[5],TrafficPoint, "10.1"),
		WayPoint(glm::vec3(-0.7722030442948, 2.9630519072679, 1.0f)),
		WayPoint(glm::vec3(-1.1212202000986, 2.6489364670445, 1.0f)),
		WayPoint(glm::vec3(-1.798313482358, 2.4674475460265, 1.0f)),
		WayPoint(glm::vec3(-2.9670375511151, 2.6695367442597, 1.0f)),
		WayPoint(glm::vec3(-3.9996644447838, 2.9172218813602, 1.0f)),
		WayPoint(glm::vec3(-5.2610950837471, 2.9975677819311, 1.0f)),
		WayPoint(glm::vec3(-6.2734534309406, 2.9413256515315, 1.0f)),
		WayPoint(glm::vec3(-7.1652929272777, 2.8690143410177, 1.0f)),
		WayPoint(glm::vec3(-7.9767865230439, 2.8368759807893, 1.0f)),
		WayPoint(glm::vec3(-8.6539814206188, 2.7802355590692, 1.0f), EndPoint),
	};

	/*9.1*/std::vector<WayPoint> waypoints6 = {
		WayPoint(glm::vec3(-8.9691922928002, 2.4267362142895, 1.0f)),
		WayPoint(glm::vec3(-8, 2.5, 1.0f)),
		WayPoint(glm::vec3(-6.7786220366297, 2.5245295292971, 1.0f)),
		WayPoint(glm::vec3(-5.2999163931711, 2.5150062509722, 1.0f)),
		WayPoint(glm::vec3(-4.3416053637149, 2.3747656125152, 1.0f)),
		WayPoint(lightspos[6],TrafficPoint, "9.1"),
		WayPoint(glm::vec3(-2.1639406497961, 1.8617126121981, 1.0f)),
		WayPoint(glm::vec3(-1.1382749591211, 1.4665019790939, 1.0f)),
		WayPoint(glm::vec3(0.0574076777885, 1.1628177737991, 1.0f)),
		WayPoint(glm::vec3(0.8287741504193, 1.6496024409932, 1.0f)),
		WayPoint(glm::vec3(0.9860430428974, 2.3198674827452, 1.0f)),
		WayPoint(glm::vec3(1.0625738467643, 2.9561189654222, 1.0f)),
		WayPoint(glm::vec3(1.2249908959054, 3.5361798552115, 1.0f)),
		WayPoint(glm::vec3(1.3874079450464, 4.0524340471241, 1.0f)),
		WayPoint(glm::vec3(1.5, 4.5, 1.0f)),
		WayPoint(glm::vec3(1.6476071514173, 4.9148711321509, 1.0f), EndPoint),
	};

	/*8.1*/std::vector<WayPoint> waypoints7 = {
		WayPoint(glm::vec3(-8.9780707032107, 2.1583753153014, 1.0f)),
		WayPoint(glm::vec3(-8.004874671439, 2.20703511689, 1.0f)),
		WayPoint(glm::vec3(-6.7762146813271, 2.2131175920885, 1.0f)),
		WayPoint(glm::vec3(-5.343248389402, 2.2229762623933, 1.0f)),
		WayPoint(glm::vec3(-4.399270258002, 2.1091351142144, 1.0f)),
		WayPoint(lightspos[7],TrafficPoint, "8.1"),
		WayPoint(glm::vec3(-2.2869957301227, 1.5459950739404, 1.0f)),
		WayPoint(glm::vec3(-1.2383506206657, 1.1278909894656, 1.0f)),
		WayPoint(glm::vec3(0.0127139351519, 0.4098887226485, 1.0f)),
		WayPoint(glm::vec3(1.4004623072924, -0.5387729565644, 1.0f)),
		WayPoint(glm::vec3(2.8887496340606, -1.1692631299271, 1.0f)),
		WayPoint(glm::vec3(3.866764134345, -1.4053972197196, 1.0f)),
		WayPoint(glm::vec3(5.0466861540049, -1.582958300348, 1.0f)),
		WayPoint(glm::vec3(6.2353914982127, -1.6954067884867, 1.0f)),
		WayPoint(glm::vec3(7.4997180666451, -1.7690467585517, 1.0f)),
		WayPoint(glm::vec3(8.8874737812391, -1.856144397543, 1.0f), EndPoint),
	};

	/*7.1*/std::vector<WayPoint> waypoints8 = {
		WayPoint(glm::vec3(-8.9799509541348, 1.8638907449656, 1.0f)),
		WayPoint(glm::vec3(-8.0092260770107, 1.9098422184389, 1.0f)),
		WayPoint(glm::vec3(-6.7915120299675, 1.8811225475181, 1.0f)),
		WayPoint(glm::vec3(-5.3476404158956, 1.8646852362819, 1.0f)),
		WayPoint(glm::vec3(-4.4729201713039, 1.8044710500736, 1.0f)),
		WayPoint(lightspos[8],TrafficPoint, "7.1"),
		WayPoint(glm::vec3(-2.4430587150794, 1.2529594145626, 1.0f)),
		WayPoint(glm::vec3(-1.2106040861149, 0.6939262654901, 1.0f)),
		WayPoint(glm::vec3(-0.1365356998153, -0.4790407504676, 1.0f)),
		WayPoint(glm::vec3(0.1179080609641, -1.2286183160069, 1.0f)),
		WayPoint(glm::vec3(0.2829526625507, -1.8956735807528, 1.0f)), /*stoplicht trein*/
		WayPoint(glm::vec3(0.4891385172183, -3.2306959961184, 1.0f)),
		WayPoint(glm::vec3(0.5995569026235, -4.136126756441, 1.0f)),
		WayPoint(glm::vec3(0.6731691595603, -4.8354431973405, 1.0f), EndPoint),
	};

	/*6.1*/std::vector<WayPoint> waypoints9 = {
		WayPoint(glm::vec3(1.3776995029531, -5.0033607423968, 1.0f)),
		WayPoint(glm::vec3(1.240331711901, -4.3623110508202, 1.0f)),
		WayPoint(lightspos[9],TrafficPoint, "6.1"),
		WayPoint(glm::vec3(0.8151456919778, -2.2363809512042, 1.0f)),
		WayPoint(glm::vec3(0.5991551629872, -1.1745396523912, 1.0f)),
		WayPoint(glm::vec3(0.3731326989372, -0.1527297628317, 1.0f)),
		WayPoint(glm::vec3(0.1730853724156, 0.6489100254638, 1.0f)),
		WayPoint(glm::vec3(0.0574076777885, 1.1628177737991, 1.0f)),
		WayPoint(glm::vec3(-0.1702132612523, 1.4263391275666, 1.0f)),
		WayPoint(glm::vec3(-0.861420251756, 1.9021049781731, 1.0f)),
		WayPoint(glm::vec3(-1.7612950821041, 2.2980994907728, 1.0f)),
		WayPoint(glm::vec3(-2.9670375511151, 2.6695367442597, 1.0f)),
		WayPoint(glm::vec3(-3.9996644447838, 2.9172218813602, 1.0f)),
		WayPoint(glm::vec3(-5.2610950837471, 2.9975677819311, 1.0f)),
		WayPoint(glm::vec3(-6.2734534309406, 2.9413256515315, 1.0f)),
		WayPoint(glm::vec3(-7.1652929272777, 2.8690143410177, 1.0f)),
		WayPoint(glm::vec3(-7.9767865230439, 2.8368759807893, 1.0f)),
		WayPoint(glm::vec3(-8.6539814206188, 2.7802355590692, 1.0f), EndPoint),
	};

	/*5.1*/std::vector<WayPoint> waypoints10 = {
		WayPoint(glm::vec3(1.8317933679565, -5.0394228135905,1.0f)),
		WayPoint(glm::vec3(1.6493525516954, -4.324862949901,1.0f)),
		WayPoint(lightspos[10],TrafficPoint, "5.1"),
		WayPoint(glm::vec3(1.2655508561342, -2.2651794953588,1.0f)),
		WayPoint(glm::vec3(1.0165189064083, -1.1373448322266,1.0f)),
		WayPoint(glm::vec3(0.9059514575216, -0.4729394361205,1.0f)),
		WayPoint(glm::vec3(0.8963982678125, 0.2362759914028,1.0f)),
		WayPoint(glm::vec3(0.8, 0.8,1.0f)),
		WayPoint(glm::vec3(0.8287741504193, 1.6496024409932,1.0f)),
		WayPoint(glm::vec3(0.9860430428974, 2.3198674827452,1.0f)),
		WayPoint(glm::vec3(1.0625738467643, 2.9561189654222, 1.0f)),
		WayPoint(glm::vec3(1.2249908959054, 3.5361798552115, 1.0f)),
		WayPoint(glm::vec3(1.3874079450464, 4.0524340471241, 1.0f)),
		WayPoint(glm::vec3(1.5, 4.5, 1.0f)),
		WayPoint(glm::vec3(1.6476071514173, 4.9148711321509, 1.0f), EndPoint),
	};

	/*5.1 Right turn*/std::vector<WayPoint> waypoints11 = {
		WayPoint(glm::vec3(1.8317933679565, -5.0394228135905,1.0f)),
		WayPoint(glm::vec3(1.6493525516954, -4.324862949901,1.0f)),
		WayPoint(lightspos[10],TrafficPoint, "5.1"),
		WayPoint(glm::vec3(1.2655508561342, -2.2651794953588, 1.0f)),
		WayPoint(glm::vec3(1.5812641907014, -1.4308044560153, 1.0f)),
		WayPoint(glm::vec3(2.3360846157252, -1.0728039115754, 1.0f)),
		WayPoint(glm::vec3(2.8887496340606, -1.1692631299271, 1.0f)),
		WayPoint(glm::vec3(3.866764134345, -1.4053972197196, 1.0f)),
		WayPoint(glm::vec3(5.0466861540049, -1.582958300348, 1.0f)),
		WayPoint(glm::vec3(6.2353914982127, -1.6954067884867, 1.0f)),
		WayPoint(glm::vec3(7.4997180666451, -1.7690467585517, 1.0f)),
		WayPoint(glm::vec3(8.8874737812391, -1.856144397543, 1.0f), EndPoint),
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
	paths.push_back(new WayPoints(waypoints11,"5.1"));

	WayPoints* splitbottomlefteast = new WayPoints
	({
		WayPoint(glm::vec3(-3.1716065658536, 0.7320769193107, 1.0f)),
		WayPoint(glm::vec3(-2.771603394783, 0.5026633359026, 1.0f)),
		WayPoint(glm::vec3(-2.1480690398787, 0.114424963981, 1.0f)),
		WayPoint(glm::vec3(-1.6657122747641, -0.2796958075151, 1.0f)),
		WayPoint(glm::vec3(-1.0972404482609, -0.825638718659, 1.0f)),
		WayPoint(glm::vec3(-0.6318822333853, -1.5689015030759, 1.0f)),
		WayPoint(glm::vec3(-0.4861123584039, -2.2304724741452, 1.0f)),// trein stoplicht
		WayPoint(glm::vec3(-0.4069809685429, -3.2807699599339, 1.0f)),
		WayPoint(glm::vec3(-0.4474318935296, -4.3324940095897, 1.0f)),
		WayPoint(glm::vec3(-0.4474318935296, -4.7673414531974, 1.0f), EndPoint),
	});

	WayPoints* splitbottomleftwest = new WayPoints
	({
		WayPoint(glm::vec3(-3.6280620229767, 1.1423242118342,1.0f)),
		WayPoint(glm::vec3(-3.976072853295, 1.2317722135855,1.0f)),
		WayPoint(glm::vec3(-4.5145460336825, 1.4063942620235,1.0f)),
		WayPoint(glm::vec3(-5, 1.5,1.0f)),
		WayPoint(glm::vec3(-5.5109123079851, 1.5989270832386,1.0f)),
		WayPoint(glm::vec3(-6.0658491843453, 1.6742888812628,1.0f)),
		WayPoint(glm::vec3(-6.6413392783484, 1.7359485341917,1.0f)),
		WayPoint(glm::vec3(-7.2921911703757, 1.7565017518347,1.0f)),
		WayPoint(glm::vec3(-7.8128726839976, 1.7565017518347,1.0f)),
		WayPoint(glm::vec3(-8.2376391819523, 1.77020389693,1.0f)),
		WayPoint(glm::vec3(-8.861086783789, 1.7770549694776,1.0f), EndPoint),
		});



	WayPoints* splittopleftsouth = new WayPoints
	({
		WayPoint(glm::vec3(-2.065470863149, 3.5176804247066, 1.0f)),
		WayPoint(glm::vec3(-2.1554209614952, 3.2523276345853, 1.0f)),
		WayPoint(glm::vec3(-2.2498685647587, 3.000467359216, 1.0f)),
		WayPoint(lightspos[16], TrafficPoint, "26.1"), // stoplicht
		WayPoint(glm::vec3(-2.5587026270678, 2.1877021252659, 1.0f)),
		WayPoint(glm::vec3(-2.9746230861281, 1.2518585251281, 1.0f)),
		WayPoint(glm::vec3(-3.0958109530275, 0.957077473291,1.0f), SplitPoint, "-1", std::vector<WayPoints*>{splitbottomlefteast,splitbottomleftwest}),
	});

	WayPoints* splittopleftnorth = new WayPoints
	({
		WayPoint(glm::vec3(-1.6, 3.8, 1.0f)),
		WayPoint(glm::vec3(-1.400323189565, 4.2560510035559, 1.0f)),
		WayPoint(glm::vec3(-1.2375001483952, 4.717382953537, 1.0f)),
		WayPoint(glm::vec3(-1.0520627959519, 5.0701662094048, 1.0f), EndPoint),
	});



	WayPoints* splittoprightwest = new WayPoints
	({
	WayPoint(glm::vec3(1.620997583112, 2.5319778394301, 1.0f)),
	WayPoint(lightspos[18], TrafficPoint, "28.1"),
	WayPoint(glm::vec3(0.7026257657899, 2.7811597497058, 1.0f)),
	WayPoint(glm::vec3(-1, 3.2, 1.0f)),
	WayPoint(glm::vec3(-1.4243749428383, 3.3045982503358, 1.0f)),
	WayPoint(glm::vec3(-1.7369176884792, 3.3977600302865, 1.0f), SplitPoint, "-1",std::vector<WayPoints*>{splittopleftnorth,splittopleftsouth})
	});



	/*std::vector<WayPoint> splittoprightnorth2 =
	{*/
	WayPoints* splittoprightnorth = new WayPoints
	({
		WayPoint(glm::vec3(2.0073804759653, 2.4268303862112,1.0f)), //split
		WayPoint(glm::vec3(2.3203058348275, 3.2435438115671, 1.0f)),
		WayPoint(glm::vec3(2.5667800763747, 3.9231287637771, 1.0f)),
		WayPoint(glm::vec3(2.8037206037346, 4.5710885732921, 1.0f)),
		WayPoint(glm::vec3(3.0001301134159, 5.0658727922079, 1.0f), EndPoint),
	});


	/*std::vector<WayPoint> splittoprightnorth =
	{*/
	WayPoints* splittoprightnorth2 = new WayPoints
	({
		WayPoint(glm::vec3(2.0073804759653, 2.4268303862112,1.0f), SplitPoint, "-1",std::vector<WayPoints*>{splittoprightwest,splittoprightnorth}), //split

	});



	WayPoints* splittoprighteast = new WayPoints
	({
	/*std::vector<WayPoint> splittoprighteast =
	{*/
		WayPoint(glm::vec3(2.8760401888494, 0.834518921357,1.0f)),
		WayPoint(glm::vec3(4.038781641347, 0.6220950021507,1.0f)),
		WayPoint(glm::vec3(5.4215626090726, 0.3515345179165,1.0f)),
		WayPoint(glm::vec3(6.8265891492556, 0.0936533925303,1.0f)),
		WayPoint(glm::vec3(7.9008314469685, 0.0659310106539,1.0f)),
		WayPoint(glm::vec3(8.8919065990519, 0.0312780333083,1.0f), EndPoint),

	});


	std::vector<WayPoint> bikewaypoints0 = {
		WayPoint(glm::vec3(2.3649879308739, -4.964727604776, 1.0f)),
		WayPoint(glm::vec3(2.1376245552665, -4.0227936201166, 1.0f)),
		WayPoint(glm::vec3(2.0206948192398, -3.3212152039565, 1.0f)), /*train 99.0*/
		WayPoint(glm::vec3(1.8712846009835, -2.3013280619459, 1.0f)),
		WayPoint(glm::vec3(2.3000269664146, -1.7686481533799, 1.0f)),
		WayPoint(lightspos[23],TrafficPoint, "22.0"),
		WayPoint(glm::vec3(2.0833062265068, -0.100244858336, 1.0f)),
		WayPoint(glm::vec3(1.923963216694, 1.103253546383, 1.0f), SplitPoint, "-1", std::vector<WayPoints*>{ splittoprightnorth2,splittoprighteast }),
	};

	bikepaths.push_back(new WayPoints(bikewaypoints0));

	WayPoints* splittoprighteast2 = new WayPoints
	({
		WayPoint(glm::vec3(1.7344430133265, 2.2393929296822,1.0f)),
		WayPoint(glm::vec3(1.6525194775252, 1.8775639798928,1.0f)),
		WayPoint(glm::vec3(1.659346438842, 1.5771776819545,1.0f)),
		WayPoint(glm::vec3(1.720789090693, 1.2563105000659,1.0f), SplitPoint, "-1",std::vector<WayPoints*>{ splittoprighteast,splittoprighteast }), //split
		});



	std::vector<WayPoint> bikewaypoints1 = {
		WayPoint(glm::vec3(2.8677185919119, 5.0589279535122, 1.0f)),
		WayPoint(glm::vec3(2.6560827910917, 4.6151754679215, 1.0f)),
		WayPoint(glm::vec3(2.430793067638, 3.9597871815106, 1.0f)),
		WayPoint(glm::vec3(2.2055033441843, 3.297571933783, 1.0f)),
		WayPoint(glm::vec3(1.905117046246, 2.4715096144527, 1.0f), SplitPoint, "-1", std::vector<WayPoints*>{ splittoprightwest,splittoprighteast2 }) //split
	};

	bikepaths.push_back(new WayPoints(bikewaypoints1));
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