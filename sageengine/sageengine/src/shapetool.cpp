#include "pch.h"
#include "shapeTool.h"




/**
 * Create a vector of indices representing a square.
 *
 * @param offSet An offset to add to the indices.
 *
 * @return A vector of unsigned 16-bit integers representing the indices of the square.
 * 
 * Generates indices to be like this:
 *   2------3
 *   |\     |
 *   |  \ T1|
 *   | T0 \ |
 *   0------1
 */

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
};

GameObject ShapeTool::createSquare(float width, uint32_t& offSet, glm::mat4 transfrom, glm::vec3 color)
{

    GameObject gameObject(
        generateSquareVertices(width),
        generateSquareIndicies(offSet),
        transfrom, 
        color);


    return gameObject;
}
