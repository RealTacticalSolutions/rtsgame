#include "pch.h"
#include "shapeTool.h"


/**
 * Create a square represented as a vector of Vertex objects.
 *
 * @param origin The center point of the square.
 * @param cellsize The size of each side of the square.
 *
 * @return A vector of vertices for the square.
 */
std::vector<Vertex> ShapeTool::createSquareVertices(glm::vec3 origin, float cellsize)
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
std::vector<uint16_t> ShapeTool::createSquareIndices(uint32_t offSet)
{
    std::vector<uint16_t> indices;

    // First Triangle (T0)
    indices.push_back(0 + offSet);
    indices.push_back(1 + offSet);
    indices.push_back(2 + offSet);


    // Second Triangle (T1)
    indices.push_back(2 + offSet);
    indices.push_back(1 + offSet);
    indices.push_back(3 + offSet);

    return indices;
};


/**
 * Create a rectangle represented as a vector of Vertex objects.
 *
 * @param origin The center point of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 *
 * @return A vector of vertices for the rectangle.
 */
std::vector<Vertex> ShapeTool::createRectangleVertices(glm::vec3 origin, float width, float height)
{
    float half_width = width / 2.0f;
    float half_height = height / 2.0f;

    std::vector<Vertex> vertices(4);

    // Bottom Left
    vertices[0].pos.x = -half_width + origin.x;
    vertices[0].pos.y = -half_height + origin.y;

    // Bottom Right
    vertices[1].pos.x = half_width + origin.x;
    vertices[1].pos.y = -half_height + origin.y;

    // Top Left
    vertices[2].pos.x = -half_width + origin.x;
    vertices[2].pos.y = half_height + origin.y;

    // Top Right
    vertices[3].pos.x = half_width + origin.x;
    vertices[3].pos.y = half_height + origin.y;

    return vertices;
};