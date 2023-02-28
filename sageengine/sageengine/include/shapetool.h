#pragma once


static class ShapeTool 
{
private:
	void setupvertices(std::vector<GameObject>& object);
	
	static std::vector<uint16_t> GenerateGridIndices(uint32_t xCells, uint32_t yCells, uint32_t Offset); 
	static std::vector<Vertex> GenerateGridVertices(uint32_t xCells, uint32_t yCells, float cellSize, float xOffset, float yOffset, float zOffset, glm::vec3 color);

public:
	static GameObject ShapeTool::generateGrid(uint32_t xCells, uint32_t yCells, float cellSize, float xOffset, float yOffset, float zOffset, uint32_t indicesoffset, glm::vec3 color);
};