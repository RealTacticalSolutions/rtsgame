#pragma once


static class ShapeTool 
{
<<<<<<< HEAD
private:


=======
private:	
	static std::vector<uint16_t> GenerateGridIndices(uint32_t xCells, uint32_t yCells, uint32_t Offset); 
	static std::vector<Vertex> GenerateGridVertices(uint32_t xCells, uint32_t yCells, float cellSize, float xOffset, float yOffset, float zOffset, glm::vec3 color);
>>>>>>> b6da4cd7a57b629668732f51f4d5d871b4c6a246

	static std::vector<Vertex> generateSquareVertices(float width);
	static std::vector<uint16_t> generateSquareIndicies(uint32_t& offSet);
public:
<<<<<<< HEAD
	static std::vector<uint16_t> createSquareIndices(uint32_t offSet);
	static std::vector<Vertex> createSquareVertices(glm::vec3 origin, float cellsize);

	static std::vector<Vertex> createRectangleVertices(glm::vec3 origin, float width, float height);
=======
	static GameObject generateGrid(uint32_t xCells, uint32_t yCells, float cellSize, float xOffset, float yOffset, float zOffset, uint32_t indicesoffset, glm::vec3 color);
	static GameObject createSquare(float width, uint32_t& offSet, glm::mat4 transfrom, glm::vec3 color);
>>>>>>> b6da4cd7a57b629668732f51f4d5d871b4c6a246
};