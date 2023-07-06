#pragma once


static class ShapeTool
{
private:
    /*
     * @brief Generates the vertices for a square shape with a specified width.
     *
     * @param width The width of the square.
     * @return The generated vertices for the square.
     */
    static std::vector<Vertex> generateSquareVertices(float width);

    /*
     * @brief Generates the indices for a square shape.
     *
     * @return The generated indices for the square.
     */
    static std::vector<uint32_t> generateSquareIndices();

    /*
     * @brief Generates the vertices for a rectangle shape with a specified width and height.
     *
     * @param width  The width of the rectangle.
     * @param height The height of the rectangle.
     * @return The generated vertices for the rectangle.
     */
    static std::vector<Vertex> generateRectangleVertices(float width, float height);

    /*
     * @brief Generates the vertices for a grid shape with specified cells, cell size, and offsets.
     *
     * @param xCells   The number of cells in the x-direction.
     * @param yCells   The number of cells in the y-direction.
     * @param cellSize The size of each cell.
     * @param xOffset  The offset in the x-direction.
     * @param yOffset  The offset in the y-direction.
     * @param zOffset  The offset in the z-direction.
     * @param color    The color of the grid.
     * @return The generated vertices for the grid.
     */
    static std::vector<Vertex> generateGridVertices(uint32_t xCells, uint32_t yCells, float cellSize, float xOffset, float yOffset, float zOffset, glm::vec3 color);

    /*
     * @brief Generates the indices for a grid shape with specified cells and offset.
     *
     * @param xCells The number of cells in the x-direction.
     * @param yCells The number of cells in the y-direction.
     * @param offset The offset of the grid indices.
     * @return The generated indices for the grid.
     */
    static std::vector<uint16_t> generateGridIndices(uint32_t xCells, uint32_t yCells, uint32_t offset);
public:

    /*
     * @brief Generates a plane mesh.
     *
     * @return The generated plane mesh.
     */
    static Mesh generatePlaneMesh();

    /*
     * @brief Generates a grid mesh between two positions with a specified cell size.
     *
     * @param startingPos The starting position of the grid.
     * @param endPos      The end position of the grid.
     * @param cellSize    The size of each grid cell.
     * @return The generated grid mesh.
     */
    static Mesh generateGrid(glm::vec4 startingPos, glm::vec4 endPos, float cellSize);

    /*
     * @brief Generates a line mesh with a specified index offset, line width, length, position, rotation, axis, and color.
     *
     * @param indexOffset   The index offset for the line mesh.
     * @param lineWidth     The width of the line.
     * @param length        The length of the line.
     * @param position      The position of the line.
     * @param rotationDeg   The rotation angle in degrees.
     * @param rotationAxis  The rotation axis.
     * @param color         The color of the line.
     * @return The generated line mesh.
     */
    static Mesh generateLine(uint32_t indexOffset, float lineWidth, float length, glm::vec3 position, float rotationDeg, glm::vec3 rotationAxis, glm::vec3 color);
    /*
     * @brief Creates a square mesh with a specified width.
     *
     * @param width The width of the square.
     * @return The generated square mesh.
     */
    static Mesh createSquare(float width);

    /*S
     * @brief Creates a rectangle mesh with a specified width and height.
     *
     * @param width  The width of the rectangle.
     * @param height The height of the rectangle.
     * @return The generated rectangle mesh.
     */
    static Mesh createRectangle(float width, float height);
};