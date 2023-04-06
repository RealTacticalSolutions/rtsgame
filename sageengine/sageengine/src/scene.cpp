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
	gameObjects.push_back(GameObject(&bluePrint.renderObject, transform, color, instanceId));

	bluePrint.renderObject.renderprops.color[instanceId] = glm::vec4(color, 1.0f);
	bluePrint.renderObject.renderprops.instances[instanceId] = transform;
}

void Scene::removeObject(int index)
{
	if (gameObjects.size() > index) {
		gameObjects.erase(gameObjects.begin() + index);
	}
}
