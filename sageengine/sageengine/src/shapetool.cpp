#include "pch.h"
#include "shapetool.h"


GameObject ShapeTool::generateGrid(uint32_t xCells, uint32_t yCells, float cellSize, float xOffset, float yOffset, float zOffset, uint32_t indicesoffset, glm::vec3 color)
{
    // Generate the vertices for the grid
    std::vector<Vertex> vertices = ShapeTool::GenerateGridVertices(xCells, yCells, cellSize, xOffset, yOffset, zOffset, color);

    // Generate the indices for the grid
    std::vector<uint16_t> indices = ShapeTool::GenerateGridIndices(xCells, yCells, indicesoffset);

    // Create a new GameObject object with the generated vertices and indices
    GameObject grid(vertices, indices, glm::mat4(1.0f), color);

    return grid;
}

std::vector<uint16_t> ShapeTool::GenerateGridIndices(uint32_t xCells, uint32_t yCells, uint32_t Offset)
{
    std::vector<uint16_t> indices;
    for (uint32_t y = 0; y < yCells; y++)
    {
        for (uint32_t x = 0; x < xCells; x++)
        {
            uint32_t vertexIndex = y * (xCells + 1) + (x + Offset);

            indices.push_back(vertexIndex);
            indices.push_back(vertexIndex + 1);
            indices.push_back(vertexIndex + xCells + 1);

            indices.push_back(vertexIndex + xCells + 1);
            indices.push_back(vertexIndex + 1);
            indices.push_back(vertexIndex + xCells + 2);
        }
    }

    return indices;
}

std::vector<Vertex> ShapeTool::GenerateGridVertices(uint32_t xCells, uint32_t yCells, float cellSize, float xOffset, float yOffset, float zOffset, glm::vec3 color)
{
    std::vector<Vertex> vertices;
    for (uint32_t y = 0; y <= yCells; y++)
    {
        for (uint32_t x = 0; x <= xCells; x++)
        {
            Vertex v;
            v.pos = {
                x * cellSize + xOffset,
                y * cellSize + yOffset,
                zOffset
            };
            v.color = color;
            v.texCoord = { 0.0f, 0.5f };
            vertices.push_back(v);
        }
    }

    return vertices;
}

std::vector<Vertex> ShapeTool::generateSquareVertices(float width)
{
    std::vector<Vertex> vertices(4);

    vertices[0].pos = glm::vec3(-width, -width, 0.0f);
    vertices[1].pos = glm::vec3(width, -width, 0.0f);
    vertices[2].pos = glm::vec3(-width, width, 0.0f);
    vertices[3].pos = glm::vec3(width, width, 0.0f);

    return vertices;
}

std::vector<uint16_t> ShapeTool::generateSquareIndicies(uint32_t& offSet) 
{

    std::vector<uint16_t> indices;

    indices.push_back(0 + offSet);
    indices.push_back(1 + offSet);
    indices.push_back(2 + offSet);

    indices.push_back(2 + offSet);
    indices.push_back(1 + offSet);
    indices.push_back(3 + offSet);

    offSet += 4;
    return indices;
}
GameObject ShapeTool::createSquare(float width, uint32_t& offSet, glm::mat4 transfrom, glm::vec3 color)
{

    GameObject gameObject(
        generateSquareVertices(width),
        generateSquareIndicies(offSet),
        transfrom, 
        color);

    return gameObject;
}

