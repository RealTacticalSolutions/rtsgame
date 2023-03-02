#pragma once

class Grid
{
private:
    static std::vector<Vertex> createBoxVertices(glm::vec3 origin, float cellsize);
    static std::vector<uint16_t> createBoxIndices(uint32_t Offset);
public:
    static std::vector<std::vector<glm::vec3>> generate_grid(int x, int y, float cellsize, glm::vec3 origin);
    static GameObject Grid::createGrid(glm::vec3 origin, float cellsize, uint32_t Offset, glm::mat4 transform, glm::vec3 color);
    static uint32_t generateGrid(std::vector<GameObject>& gameObjects, std::vector<std::vector<glm::vec3>>& grid, float cellsize, uint32_t offSet, glm::mat4 transform, glm::vec3 color);
};