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

GameObject ShapeTool::generatePlane(uint32_t xCells, uint32_t yCells, float cellSize, float xOffset, float yOffset, float zOffset, uint32_t indicesoffset, glm::vec3 color)
{
    // Generate the vertices for the grid
    std::vector<Vertex> vertices = ShapeTool::GenerateGridVertices(xCells, yCells, cellSize, xOffset, yOffset, zOffset, color);

    // Generate the indices for the grid
    std::vector<uint16_t> indices = ShapeTool::GenerateGridIndices(xCells, yCells, indicesoffset);

    // Create a new GameObject object with the generated vertices and indices
    GameObject grid({ vertices, indices }, glm::mat4(1.0f), color, "../../../textures/1.jpg");

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
            v.texCoord = { 1.0f * x , 1.0f * y };
            vertices.push_back(v);
        }
    }

    return vertices;
}


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

GameObject ShapeTool::generateGrid(glm::vec4 startingpos, glm::vec4 endpos, float cellSize, uint16_t indexOffset) {
    Mesh grid;
    size_t cellCountX = 10;
    size_t cellCountY = 10;

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

    return GameObject(grid, glm::mat4(1.0f), glm::vec3(1.0f));
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

std::vector<Vertex> ShapeTool::generateRectangleVertices(float width, float height)
{
    std::vector<Vertex> vertices(4);

    vertices[0].pos = glm::vec3(-width, -height, 0.0f);
    vertices[1].pos = glm::vec3(width, -height, 0.0f);
    vertices[2].pos = glm::vec3(-width, height, 0.0f);
    vertices[3].pos = glm::vec3(width, height, 0.0f);

    return vertices;
}

GameObject ShapeTool::createSquare(float width, uint32_t& offSet, glm::mat4 transfrom, glm::vec3 color)
{

    GameObject gameObject({
        generateSquareVertices(width),
        generateSquareIndicies(offSet),
        },
        transfrom, 
        color);

    return gameObject;
}

GameObject ShapeTool::createRectangle(float width,float height, uint32_t& offSet, glm::mat4 transfrom, glm::vec3 color)
{

    GameObject gameObject({
        generateRectangleVertices(width, height),
        generateSquareIndicies(offSet),
        },
        transfrom,
        color);

    return gameObject;
}
