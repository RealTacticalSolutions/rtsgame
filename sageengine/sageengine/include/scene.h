#pragma once

class renderer;

class Scene {

private:
	

public:
	Scene() {};

	std::vector<GameObject> bluePrints;
	std::vector<GameObject> gameObjects;
	std::vector<RenderObject> renderObjects;

	void blueprintObject(GameObject gameObject);
	void instantiateObject(int index, int instanceIndex, glm::mat4 transform);
	void removeObject();

	std::unique_ptr<renderer> renderer;

};