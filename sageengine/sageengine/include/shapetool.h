#pragma once


static class ShapeTool 
{
private:



public:
	static std::vector<uint16_t> createSquareIndices(uint32_t offSet);
	static std::vector<Vertex> createSquareVertices(glm::vec3 origin, float cellsize);

	static std::vector<Vertex> createRectangleVertices(glm::vec3 origin, float width, float height);
};