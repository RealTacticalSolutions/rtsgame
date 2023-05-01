#pragma once

class renderer;

class Scene {

private:
	

public:
	Scene() {};

	std::vector<BluePrint> bluePrints;
	std::vector<std::unique_ptr<GameObject>> gameObjects;
	std::vector<RenderObject> renderObjects;

	void blueprintObject(Mesh mesh);
	void blueprintObject(Mesh mesh, char* texture);
	void instantiateObject(BluePrint bluePrint, glm::mat4 transform, glm::vec3 color);
	void instantiateCar(BluePrint bluePrint, glm::mat4 transform, glm::vec3 color, WayPoints& path);
	void instantiateBike(BluePrint bluePrint, glm::mat4 transform, glm::vec3 color, WayPoints* path);
	void removeObject(int index);

	std::unique_ptr<renderer> renderer;

};