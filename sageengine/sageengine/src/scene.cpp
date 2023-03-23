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
	int instances = bluePrint.renderObject.instanceCount;
	gameObjects.push_back(GameObject(&bluePrint.renderObject, transform, color));

	bluePrint.renderObject.renderprops.color[instances - 1] = glm::vec4(color, 1.0f);
	bluePrint.renderObject.renderprops.instances[instances - 1] = transform;
}

void Scene::removeObject()
{
}
