#pragma once

class GameObject
{
public:
	const Mesh mesh;
	Properties properties;

	GameObject(Mesh mesh, glm::mat4 transform, glm::vec3 color) : mesh(mesh), properties{transform, color} {

	};
	
private:

};