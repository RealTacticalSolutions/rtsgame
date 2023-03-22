#include "pch.h"
#include "scene.h"

void Scene::blueprintObject(Mesh mesh)
{
	GameObject gameobject(mesh, glm::mat4(1.0f), glm::vec3(1.0f));
	bluePrints.push_back(gameobject);
	renderObjects.push_back({ gameobject.mesh , {gameobject.properties.transform} , gameobject.texture });
}

void Scene::blueprintObject(Mesh mesh, char* texture)
{
	GameObject gameobject(mesh, glm::mat4(1.0f), glm::vec3(1.0f), texture);
	bluePrints.push_back(gameobject);
	renderObjects.push_back({ gameobject.mesh , {gameobject.properties.transform} , gameobject.texture });
}

void Scene::instantiateObject(int index, int instanceIndex, glm::mat4 transform, glm::vec3 color)
{
	renderObjects[index].instanceCount += 1;
	renderObjects[index].renderprops.color[instanceIndex] = glm::vec4(color, 1.0f);
	renderObjects[index].renderprops.instances[instanceIndex] = transform;
}



void Scene::removeObject()
{
}
