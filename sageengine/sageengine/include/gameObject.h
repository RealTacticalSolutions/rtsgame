#pragma once

class GameObject
{
public:
	const std::vector<Vertex> vertices;
	const std::vector<uint16_t> indices;
	glm::mat4 transform;

	GameObject(std::vector<Vertex> vertices, std::vector<uint16_t> indices,  glm::mat4 transform) : vertices(vertices), indices(indices), transform(transform) {

	};
	
private:
	
};