#include "pch.h"
#include "shapeTool.h"


<<<<<<< HEAD
/**
 * Create a square represented as a vector of Vertex objects.
 *
 * @param origin The center point of the square.
 * @param cellsize The size of each side of the square.
 *
 * @return A vector of vertices for the square.
 */
std::vector<Vertex> ShapeTool::createSquareVertices(glm::vec3 origin, float cellsize)
=======
GameObject ShapeTool::generateGrid(uint32_t xCells, uint32_t yCells, float cellSize, float xOffset, float yOffset, float zOffset, uint32_t indicesoffset, glm::vec3 color)
>>>>>>> b6da4cd7a57b629668732f51f4d5d871b4c6a246
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

<<<<<<< HEAD

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
=======
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

>>>>>>> b6da4cd7a57b629668732f51f4d5d871b4c6a246
    indices.push_back(0 + offSet);
    indices.push_back(1 + offSet);
    indices.push_back(2 + offSet);

<<<<<<< HEAD

    // Second Triangle (T1)
=======
>>>>>>> b6da4cd7a57b629668732f51f4d5d871b4c6a246
    indices.push_back(2 + offSet);
    indices.push_back(1 + offSet);
    indices.push_back(3 + offSet);

<<<<<<< HEAD
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
=======
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

>>>>>>> b6da4cd7a57b629668732f51f4d5d871b4c6a246
