#pragma once

class renderer;

class Scene {

private:
	

public:
	Scene() {};

	std::vector<BluePrint> bluePrints;
	std::vector<std::unique_ptr<GameObject>> gameObjects;
	std::vector<RenderObject> renderObjects;

	/*
	* @brief Creates a blueprint for an object with a specified mesh.
	*
	* @param mesh The mesh for the object.
	 */
	void blueprintObject(Mesh mesh);

	/*
	 * @brief Creates a blueprint for an object with a specified mesh and texture.
	 *
	 * @param mesh     The mesh for the object.
	 * @param texture  The texture for the object.
	 */
	void blueprintObject(Mesh mesh, char* texture);

	/*
	 * @brief Instantiates an object based on a blueprint with a specified transform and color.
	 *
	 * @param bluePrint The blueprint for the object.
	 * @param transform The transform matrix for the object.
	 * @param color     The color of the object.
	 */
	void instantiateObject(BluePrint bluePrint, glm::mat4 transform, glm::vec3 color);

	/*
	 * @brief Removes an object at the specified index from the scene.
	 *
	 * @param index The index of the object to remove.
	 */
	void removeObject(int index);

	std::unique_ptr<renderer> renderer;

};