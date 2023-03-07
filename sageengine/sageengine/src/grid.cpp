#include "pch.h"
#include "grid.h"


/**
 * Generate a 2D grid of points with the specified dimensions, cell size, and origin point.
 *
 * @param x The number of cells in the x direction of the grid.
 * @param y The number of cells in the y direction of the grid.
 * @param cellsize The size of each cell in the grid.
 * @param origin The center point of the grid.
 *
 * @return A 2D vector of glm::vec3 points representing the grid.
 */
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

/**
* Construct a game object representing a square grid with the given origin, cell size, offset, transform and color.
* 
* @param origin The position of the center of the grid.
* @param cellsize The size of each cell of the grid.
* @param offSet The offset for the vertex indices of the square grid.
* @param transform The transformation matrix for the grid.
* @param color The color of the grid.
* 
* @return A game object representing a square grid.
*/
void Grid::constructSquare(glm::vec3 origin, float cellsize, uint32_t& offSet, glm::mat4 transform, glm::vec3 color)
{
    // Todo: make this function

}

/**
* Generates a grid of GameObjects based on a 2D vector of points and a set of parameters.
* 
* @param gameObjects - a reference to a vector of GameObjects to store the generated grid.
* @param grid - a 2D vector of points representing the grid.
* @param cellsize - a float value representing the size of each cell in the grid.
* @param offSet - an integer value representing the offset to be used when generating the indices for each GameObject.
* @param transform - a 4x4 transformation matrix to be applied to each GameObject.
* @param color - a vec3 value representing the color to be used for each GameObject.
* 
* @return the total number of GameObjects generated.
*/
void Grid::generateGrid(std::vector<GameObject>& gameObjects,std::vector<std::vector<glm::vec3>>& grid, float cellsize, uint32_t& offSet, glm::mat4 transform, glm::vec3 color)
{
    for (size_t i = 0; i < grid.size(); i++)
    {
        for (size_t j = 0; j < grid[i].size(); j++)
        {
            // Todo: fix this function
            //gameObjects.push_back(constructSquare(grid[i][j],cellsize, offSet, transform, color));
            offSet += 4;
        }
    }

}

/**
* Creates a square GameObject and adds it to the provided vector of GameObjects.
* 
* @param gameObjects A vector of GameObjects to which the newly created square will be added.
* @param origin The position of the square's center.
* @param size The size of the square.
* @param offSet The offset value used to generate indices for the square's vertices.
* @param transform The transformation matrix for the square.
* @param color The color of the square.
* 
*/
void Grid::creatSquare(std::vector<GameObject>& gameObjects, glm::vec3 origin, float size, uint32_t& offSet, glm::mat4 transfrom, glm::vec3 color)
{
    // Todo: fix this function
    //gameObjects.push_back(constructSquare(origin, size, offSet, transfrom, color));
    offSet += 4;
};

/**
* Constructs and adds a rectangle made up of two triangles to a vector of GameObjects.
* using the provided origin, width, height, transformation matrix, and color.
* Automatically computes the indices and updates the given offset.
* 
* @param gameObjects a vector of GameObjects to add the rectangle to
* @param origin the origin point of the rectangle
* @param width the width of the rectangle
* @param height the height of the rectangle
* @param offSet an offset value used to calculate the index of each vertex
* @param transform the transformation matrix to apply to the rectangle
* @param color the color to apply to the rectangle
* 
*/
void Grid::createRectangle(std::vector<GameObject>& gameObjects,glm::vec3 origin, float width, float height, uint32_t& offSet, glm::mat4 transform, glm::vec3 color)
{
    // Todo: fix this function
    //gameObjects.push_back(constructRectangle(origin, width,height, RECTANGLE, offSet, transform, color));

    offSet += 4;
}

/**
* Constructs and adds a rectangle GameObject to the given vector of GameObjects,
* using the provided vertices, transformation matrix, and color.
* Automatically computes the indices and updates the given offset.
*
* @param gameObjects A vector of GameObjects to add the new rectangle to.
* @param vertices A vector of vertices defining the rectangle.
* @param offSet An offset value used to compute the indices for the new rectangle.
*               The value is updated to account for the added vertices.
* @param transform A 4x4 transformation matrix to apply to the rectangle vertices.
* @param color The color to use for the rectangle vertices.
* 
*/
void Grid::createRectangle(std::vector<GameObject>& gameObjects, std::vector<Vertex> vertices, uint32_t& offSet, glm::mat4 transform, glm::vec3 color)
{
    // Todo: fix this function
    //gameObjects.push_back(constructRectangle(vertices, RECTANGLE, offSet, transform, color));

    offSet += 4;
}

/**
* Constructs a rectangle GameObject using the given parameters.
* 
* @param origin The bottom-left position of the rectangle.
* @param width The width of the rectangle.
* @param height The height of the rectangle.
* @param offSet The offset used for indexing indices.
* @param transform The transformation matrix of the rectangle.
* @param color The color of the rectangle.
* 
* @return A GameObject representing the rectangle.
*/
void Grid::constructRectangle(glm::vec3 origin, float width, float height, CollisionType collisiontype, uint32_t& offSet, glm::mat4 transform, glm::vec3 color)
{
    // Todo: make this function

};

/**
* Constructs a rectangle GameObject from the provided vertices and other parameters.
* 
* @param vertices The vertices of the rectangle.
* @param collisiontype The collision type of the rectangle.
* @param offSet A reference to an offset value that will be incremented by the number of vertices in the rectangle.
* @param transform The transform matrix to apply to the rectangle vertices.
* @param color The color to use for the rectangle.
* 
* @return A new GameObject representing the rectangle.
*/
void Grid::constructRectangle(std::vector<Vertex> vertices, CollisionType collisiontype, uint32_t& offSet, glm::mat4 transform, glm::vec3 color)
{
    // Todo: make this function
    GameObject gameObject(
   
    );

}
