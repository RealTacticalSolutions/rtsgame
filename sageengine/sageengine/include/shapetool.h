#pragma once


static class ShapeTool 
{
private:	
	static std::vector<Vertex> generateSquareVertices(float width);
	static std::vector<uint16_t> generateSquareIndicies();

	static std::vector<Vertex> generateRectangleVertices(float width, float height);


	static std::vector<Vertex> GenerateGridVertices(uint32_t xCells, uint32_t yCells, float cellSize, float xOffset, float yOffset, float zOffset, glm::vec3 color);
	static std::vector<uint16_t> ShapeTool::GenerateGridIndices(uint32_t xCells, uint32_t yCells, uint32_t Offset);
public:

	static Mesh generatePlaneMesh();
	static Mesh generateGrid(glm::vec4 startingpos, glm::vec4 endpos, float cellSize);
	static Mesh generateLine(uint16_t indexoffset, float linewidth, float length, glm::vec3 position, float rotationDeg, glm::vec3 rotationAxis, glm::vec3 color);
	static Mesh createSquare(float width);
	static Mesh createRectangle(float width, float height);
};