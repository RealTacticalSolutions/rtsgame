#include "pch.h"
#include "grid.h"


// Todo: draws the grid from up to down, and then right to left not optimal, change to be from left to right up down.
std::vector<std::vector<glm::vec3>> Grid::generate_grid(int x, int y, float cellsize, glm::vec3 origin) {
    std::vector<std::vector<glm::vec3>> grid(x, std::vector<glm::vec3>(y));
    float cellsizeincreased = cellsize * 2;
    float x_offset = (float)(x - 1) / 2.0f * cellsizeincreased;
    float y_offset = (float)(y - 1) / 2.0f * cellsizeincreased;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            grid[i][j] = { origin.x + (i * cellsizeincreased), origin.y + (j * cellsizeincreased), origin.z };
        }
    }
    return grid;
}

std::vector<Vertex> Grid::createBoxVertices(glm::vec3 origin, float cellsize)
{
    std::vector<Vertex> vertices(4);
    // Bottom Left
    vertices[0].pos.x = (origin.x + cellsize);
    vertices[0].pos.y = (origin.y + cellsize);

    // Bottom right
    vertices[1].pos.x = (origin.x - cellsize);
    vertices[1].pos.y = (origin.y + cellsize);

    // Top Left
    vertices[2].pos.x = (origin.x + cellsize);
    vertices[2].pos.y = (origin.y - cellsize);

    // Top Right
    vertices[3].pos.x = (origin.x - cellsize);
    vertices[3].pos.y = (origin.y - cellsize);

    return vertices;
}

std::vector<uint16_t> Grid:: createBoxIndices(uint32_t offSet)
{
    std::vector<uint16_t> indices;
    indices.push_back(0 + offSet);
    indices.push_back(1 + offSet);
    indices.push_back(2 + offSet);

    indices.push_back(2 + offSet);
    indices.push_back(1 + offSet);
    indices.push_back(3 + offSet);

    return indices;
};

GameObject Grid::createGrid(glm::vec3 origin, float cellsize, uint32_t offSet, glm::mat4 transform, glm::vec3 color)
{
        GameObject gameObject(
            createBoxVertices(origin, cellsize),
            createBoxIndices(offSet),
            transform,
            color
        );
        return gameObject;
}

uint32_t Grid::generateGrid(std::vector<GameObject>& gameObjects,std::vector<std::vector<glm::vec3>>& grid, float cellsize, uint32_t offSet, glm::mat4 transform, glm::vec3 color)
{
    for (size_t i = 0; i < grid.size(); i++)
    {
        for (size_t j = 0; j < grid[i].size(); j++)
        {
            gameObjects.push_back(createGrid(grid[i][j],cellsize, offSet, transform, color));
            offSet += 4;
        }
    }

    return offSet;
}