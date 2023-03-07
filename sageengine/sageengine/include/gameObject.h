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
<<<<<<< HEAD
	GameObject(std::vector<Vertex> vertices, std::vector<uint16_t> indices, CollisionType collisiontype, glm::mat4 transform, glm::vec3 color) : vertices(vertices), indices(indices), collisiontype(collisiontype), properties{ transform, color } {

	};
	GameObject(glm::mat4 transform, glm::vec3 color) :  properties{ transform, color } {

	};
=======

>>>>>>> b6da4cd7a57b629668732f51f4d5d871b4c6a246
	
private:

};