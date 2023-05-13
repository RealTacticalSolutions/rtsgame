#include "pch.h"
#include "scene.h"

void Scene::blueprintObject(Mesh mesh)
{
	renderObjects.push_back({ mesh , {} , "../../../textures/default.png" });
	BluePrint bluePrint(renderObjects.back());
	bluePrints.push_back(bluePrint);
	
}

void Scene::blueprintObject(Mesh mesh, char* texture)
{
	renderObjects.push_back({ mesh , {} , texture });
	BluePrint bluePrint(renderObjects.back());
	bluePrints.push_back(bluePrint);
}

void Scene::instantiateObject(BluePrint bluePrint, glm::mat4 transform, glm::vec3 color)
{
	bluePrint.renderObject.instanceCount += 1;
	int instanceId = bluePrint.renderObject.instanceCount - 1;
	std::unique_ptr<GameObject> obj = std::make_unique<GameObject>(&bluePrint.renderObject, transform, color, instanceId);
	gameObjects.push_back(std::move(obj));

	bluePrint.renderObject.renderprops.color[instanceId] = glm::vec4(color, 1.0f);
	bluePrint.renderObject.renderprops.instances[instanceId] = transform;
}
void Scene::instantiateCar(BluePrint bluePrint, glm::mat4 transform, glm::vec3 color, WayPoints* path)
{
	bluePrint.renderObject.instanceCount += 1;
	int instanceId = bluePrint.renderObject.instanceCount - 1;
	std::unique_ptr<Car> car = std::make_unique<Car>(&bluePrint.renderObject, transform, color, instanceId, path, 0);
	gameObjects.push_back(std::move(car));

	bluePrint.renderObject.renderprops.color[instanceId] = glm::vec4(color, 1.0f);
	bluePrint.renderObject.renderprops.instances[instanceId] = transform;
}
void Scene::instantiateTrain(BluePrint bluePrint, glm::mat4 transform, glm::vec3 color, WayPoints* path)
{
	bluePrint.renderObject.instanceCount += 1;
	int instanceId = bluePrint.renderObject.instanceCount - 1;
	std::unique_ptr<Train> train = std::make_unique<Train>(&bluePrint.renderObject, transform, color, instanceId, path, 0);
	gameObjects.push_back(std::move(train));

	bluePrint.renderObject.renderprops.color[instanceId] = glm::vec4(color, 1.0f);
	bluePrint.renderObject.renderprops.instances[instanceId] = transform;
}

void Scene::instantiateBike(BluePrint bluePrint, glm::mat4 transform, glm::vec3 color, WayPoints* path)
{
	bluePrint.renderObject.instanceCount += 1;
	int instanceId = bluePrint.renderObject.instanceCount - 1;
	std::unique_ptr<Bike> bike = std::make_unique<Bike>(&bluePrint.renderObject, transform, color, instanceId, path, 0);
	gameObjects.push_back(std::move(bike));

	bluePrint.renderObject.renderprops.color[instanceId] = glm::vec4(color, 1.0f);
	bluePrint.renderObject.renderprops.instances[instanceId] = transform;
}

void Scene::removeObject(int index)
{
	if (gameObjects.size() > index) {
		//gameObjects[index]->renderObject->instanceCount -= 1;

		gameObjects.erase(gameObjects.begin() + index);
	}


}
