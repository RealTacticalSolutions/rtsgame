#pragma once

class GameObject
{
public:
	const std::vector<Vertex> vertices;
	const std::vector<uint16_t> indices;
	Properties properties;
	CollisionType collisiontype;
	GameObject(std::vector<Vertex> vertices, std::vector<uint16_t> indices, glm::mat4 transform, glm::vec3 color) : vertices(vertices), indices(indices), properties{transform, color} {

	};
	GameObject(std::vector<Vertex> vertices, std::vector<uint16_t> indices, CollisionType collisiontype, glm::mat4 transform, glm::vec3 color) : vertices(vertices), indices(indices), collisiontype(collisiontype), properties{ transform, color } {

	};
	GameObject(glm::mat4 transform, glm::vec3 color) :  properties{ transform, color } {

	};
	
private:

};