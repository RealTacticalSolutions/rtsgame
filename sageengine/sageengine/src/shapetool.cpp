#include "pch.h"
#include "shapetool.h"

Mesh ShapeTool::generatePlaneMesh() {
    return Mesh();
}

Mesh ShapeTool::generateLine(uint16_t indexoffset, float linewidth, float length, glm::vec3 position, float rotationDeg, glm::vec3 rotationAxis, glm::vec3 color) {
    int i = indexoffset;

    Mesh mesh = { {
            {   {0.0f, 0.0f, 0.01f}, color, {0.5f, 0.0f} },
            {   {linewidth, 0.0f, 0.01f}, color, {0.5f, 0.0f} },
            {   {linewidth, length, 0.01f}, color, {0.5f, 0.0f} },
            {   {0.0f, length, 0.01f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.0f} },
        },

        {(uint16_t)(i), (uint16_t)(i + 1), (uint16_t)(i + 2), (uint16_t)(i), (uint16_t)(i + 2), (uint16_t)(i + 3)}
    };

    for (int i = 0; i < 4; i++) {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform = glm::rotate(transform, -glm::radians(rotationDeg), rotationAxis);
        mesh.vertices[i].pos = transform * glm::vec4(mesh.vertices[i].pos, 1.0f);
    }

    return mesh;
}

Mesh ShapeTool::generateGrid(glm::vec4 startingpos, glm::vec4 endpos, float cellSize) {
    Mesh grid;
    size_t cellCountX = 10;
    size_t cellCountY = 10;

    uint16_t indexOffset = 0;

    float xLength = endpos.x - startingpos.x;
    float yLength = endpos.y - startingpos.y;

    for (size_t x = 0; x <= cellCountX; x++)
    {
        Mesh temp = ShapeTool::generateLine(indexOffset, 0.01, yLength, glm::vec3(startingpos.x + (xLength / cellCountX) * x, startingpos.y, 0.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.1f, 1.0f, 0.1f));
        grid.vertices.insert(grid.vertices.end(), temp.vertices.begin(), temp.vertices.end());
        grid.indices.insert(grid.indices.end(), temp.indices.begin(), temp.indices.end());
        indexOffset += 4;
    }

    for (size_t y = 0; y <= cellCountY; y++)
    {
        Mesh temp = ShapeTool::generateLine(indexOffset, 0.01, xLength, glm::vec3(startingpos.x, startingpos.y + (yLength / cellCountY) * y, 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.1f, 1.0f, 0.1f));
        grid.vertices.insert(grid.vertices.end(), temp.vertices.begin(), temp.vertices.end());
        grid.indices.insert(grid.indices.end(), temp.indices.begin(), temp.indices.end());
        indexOffset += 4;
    }

    return grid;
}

std::vector<Vertex> ShapeTool::generateSquareVertices(float width)
{
    std::vector<Vertex> vertices(4);

    vertices[0].pos = glm::vec3(-width, -width, 0.0f);
    vertices[1].pos = glm::vec3(width, -width, 0.0f);
    vertices[2].pos = glm::vec3(-width, width, 0.0f);
    vertices[3].pos = glm::vec3(width, width, 0.0f);

    vertices[1].texCoord.x = 1.0f;
    vertices[1].texCoord.y = 1.0f;
    vertices[0].texCoord.y = 1.0f;
    vertices[3].texCoord.x = 1.0f;

    return vertices;
}

std::vector<uint16_t> ShapeTool::generateSquareIndicies() 
{
    std::vector<uint16_t> indices;

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    indices.push_back(2);
    indices.push_back(1);
    indices.push_back(3);

    return indices;
}

std::vector<Vertex> ShapeTool::generateRectangleVertices(float width, float height)
{
    std::vector<Vertex> vertices(4);

    vertices[0].pos = glm::vec3(-width, -height, 0.0f);
    vertices[1].pos = glm::vec3(width, -height, 0.0f);
    vertices[2].pos = glm::vec3(-width, height, 0.0f);
    vertices[3].pos = glm::vec3(width, height, 0.0f);

    return vertices;
}

Mesh ShapeTool::createSquare(float width)
{

    Mesh mesh({
        generateSquareVertices(width),
        generateSquareIndicies()
        });
      

    return mesh;
}

Mesh ShapeTool::createRectangle(float width,float height)
{

    Mesh mesh({
        generateRectangleVertices(width, height),
        generateSquareIndicies(),
        });

    return mesh;
}
