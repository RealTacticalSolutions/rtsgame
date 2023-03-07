#pragma once

class GameObject
{
public:
	const std::vector<Vertex> vertices;
	const std::vector<uint16_t> indices;
	Properties properties;

	GameObject(std::vector<Vertex> vertices, std::vector<uint16_t> indices, glm::mat4 transform, glm::vec3 color) : vertices(vertices), indices(indices), properties{transform, color} {

	};

	
private:

};