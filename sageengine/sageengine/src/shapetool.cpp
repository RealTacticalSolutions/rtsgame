#include "pch.h"
#include "shapetool.h"


//void ShapeTool::setupvertices(std::vector<GameObject>& object)
//{
//    int XCELL = 2;
//    int YCELL = 2;
//    float GRIDSIZE = 1.0f;
//    glm::vec3 green = { 0.0f,1.0f,0.0f };
//    glm::vec3 black = { 0.0f,0.0f,0.0f };
//
//    vertices = GenerateGridVertices(XCELL, YCELL, GRIDSIZE, 1, 1, 0, green);
//    indices = GenerateGridIndices(XCELL, YCELL, 0);
//
//
//    glm::vec3 red = { 1.0f,0.0f,0.0f };
//    std::vector<Vertex> vertices2 = GenerateGridVertices(XCELL, YCELL, GRIDSIZE, -3.0f, 1.0f, 0.0f, red);
//
//     Calculate offset for second grid's indices
//    uint16_t offset = static_cast<uint16_t>(vertices.size());
//
//    std::vector<uint16_t> indices2 = GenerateGridIndices(XCELL, YCELL, offset);
//
//     Append the second grid's vertices and indices to the existing vectors
//    vertices.insert(vertices.end(), vertices2.begin(), vertices2.end());
//    indices.insert(indices.end(), indices2.begin(), indices2.end());
//
//    vertices2 = GenerateGridVertices(XCELL, YCELL, GRIDSIZE, 1.0f, -3.0f, 0.0f, red);
//
//    offset = static_cast<uint16_t>(vertices.size());
//
//    indices2 = GenerateGridIndices(XCELL, YCELL, offset);
//
//     Append the second grid's vertices and indices to the existing vectors
//    vertices.insert(vertices.end(), vertices2.begin(), vertices2.end());
//    indices.insert(indices.end(), indices2.begin(), indices2.end());
//
//    vertices2 = GenerateGridVertices(XCELL, YCELL, GRIDSIZE, -3.0f, -3.0f, 0.0f, red);
//
//    offset = static_cast<uint16_t>(vertices.size());
//
//    indices2 = GenerateGridIndices(XCELL, YCELL, offset);
//
//     Append the second grid's vertices and indices to the existing vectors
//    vertices.insert(vertices.end(), vertices2.begin(), vertices2.end());
//    indices.insert(indices.end(), indices2.begin(), indices2.end());
//}

GameObject ShapeTool::generateGrid(uint32_t xCells, uint32_t yCells, float cellSize, float xOffset, float yOffset, float zOffset, uint32_t indicesoffset, glm::vec3 color)
{
    // Generate the vertices for the grid
    std::vector<Vertex> vertices = ShapeTool::GenerateGridVertices(xCells, yCells, cellSize, xOffset, yOffset, zOffset, color);

    // Generate the indices for the grid
    std::vector<uint16_t> indices = ShapeTool::GenerateGridIndices(xCells, yCells, indicesoffset);

    // Create a new GameObject object with the generated vertices and indices
    GameObject grid(vertices, indices, glm::mat4(1.0f));

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
            v.texCoord = { 0.0f, 0.0f };
            vertices.push_back(v);
        }
    }

    return vertices;
}