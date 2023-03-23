#pragma once

class renderer;

class Scene {

private:
	

public:
	Scene() {};

	std::vector<BluePrint> bluePrints;
	std::vector<GameObject> gameObjects;
	std::vector<RenderObject> renderObjects;

	void blueprintObject(Mesh mesh);
	void blueprintObject(Mesh mesh, char* texture);
	void instantiateObject(BluePrint bluePrint, glm::mat4 transform, glm::vec3 color);
	void removeObject();

	std::unique_ptr<renderer> renderer;

};