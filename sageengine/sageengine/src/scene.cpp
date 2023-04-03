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
void Scene::instantiateCar(BluePrint bluePrint, glm::mat4 transform, glm::vec3 color, WayPoints& path)
{
	bluePrint.renderObject.instanceCount += 1;
	int instanceId = bluePrint.renderObject.instanceCount - 1;
	std::unique_ptr<Car> car = std::make_unique<Car>(&bluePrint.renderObject, transform, color, instanceId, path, 0);
	gameObjects.push_back(std::move(car));

	bluePrint.renderObject.renderprops.color[instanceId] = glm::vec4(color, 1.0f);
	bluePrint.renderObject.renderprops.instances[instanceId] = transform;
}

void Scene::removeObject(int index)
{
	if (gameObjects.size() > index) {
		int removeid = gameObjects[index]->instanceId;
		int blueprintindex = 2; // Todo find a proper way to get blueprint id
		gameObjects[index]->renderObject->instanceCount -= 1;
		gameObjects[index]->instanceId -= 1;
		gameObjects.erase(gameObjects.begin() + index);

		int arraylenght = gameObjects[index]->renderObject->instanceCount;
		for (int i = removeid; i < arraylenght - 1; i++) {
			renderObjects[blueprintindex].renderprops.instances[i] = renderObjects[blueprintindex].renderprops.instances[i +1];
			renderObjects[blueprintindex].renderprops.color[i] = renderObjects[blueprintindex].renderprops.color[i + 1];
		}
			// set last new index to 0
			renderObjects[blueprintindex].renderprops.instances[arraylenght - 1] = glm::mat4(0);
			renderObjects[blueprintindex].renderprops.color[arraylenght - 1] = glm::vec4(0.0f,0.0f,0.0f,0.0f);
				
		}
	
}
