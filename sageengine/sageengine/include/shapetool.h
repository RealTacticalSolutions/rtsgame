#pragma once


static class ShapeTool 
{

private:	
	static std::vector<Vertex> generateSquareVertices(float width);
	static std::vector<uint16_t> generateSquareIndicies(uint32_t& offSet);

public:
	static GameObject createSquare(float width, uint32_t& offSet, glm::mat4 transfrom, glm::vec3 color);

};