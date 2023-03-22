#include "pch.h"
#include "scene.h"

void Scene::blueprintObject(GameObject gameobject)
{
	bluePrints.push_back(gameobject);
	renderObjects.push_back({ gameobject.mesh , {gameobject.properties.transform} , gameobject.texture });
	//renderer->createObject(mesh, transform);
}

void Scene::instantiateObject(int index, int instanceIndex, glm::mat4 transform)
{
	renderObjects[index].instanceCount += 1;
	renderObjects[index].renderprops.color = glm::vec3(1.0f, 1.0f, 1.0f);
	renderObjects[index].renderprops.instances[instanceIndex] = transform;
}



void Scene::removeObject()
{
}
