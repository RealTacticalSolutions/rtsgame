#pragma once

class renderer;

class Scene {

private:
	

public:
	Scene() {};

	std::vector<GameObject> bluePrints;
	std::vector<GameObject> gameObjects;
	std::vector<RenderObject> renderObjects;

	void blueprintObject(Mesh mesh);
	void blueprintObject(Mesh mesh, char* texture);
	void instantiateObject(int index, int instanceIndex, glm::mat4 transform, glm::vec3 color);
	void removeObject();

	std::unique_ptr<renderer> renderer;

};