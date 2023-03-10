#pragma once


static class ShapeTool 
{
private:	
	static std::vector<uint16_t> GenerateGridIndices(uint32_t xCells, uint32_t yCells, uint32_t Offset); 
	static std::vector<Vertex> GenerateGridVertices(uint32_t xCells, uint32_t yCells, float cellSize, float xOffset, float yOffset, float zOffset, glm::vec3 color);
	

	static std::vector<Vertex> generateSquareVertices(float width);
	static std::vector<uint16_t> generateSquareIndicies(uint32_t& offSet);
public:

	static GameObject generatePlane(uint32_t xCells, uint32_t yCells, float cellSize, float xOffset, float yOffset, float zOffset, uint32_t indicesoffset, glm::vec3 color);
	static Mesh generatePlaneMesh();
	static GameObject generateGrid(glm::vec4 startingpos, glm::vec4 endpos, float cellSize, uint16_t indexOffset);
	static Mesh generateLine(uint16_t indexoffset, float linewidth, float length, glm::vec3 position, float rotationDeg, glm::vec3 rotationAxis, glm::vec3 color);
	static GameObject createSquare(float width, uint32_t& offSet, glm::mat4 transfrom, glm::vec3 color);

};