#pragma once

class Grid
{
private:

    static GameObject constructSquare(glm::vec3 origin, float cellsize, uint32_t& Offset, glm::mat4 transform, glm::vec3 color);
    static GameObject constructRectangle(glm::vec3 origin, float width, float height, CollisionType collisiontype, uint32_t& offSet, glm::mat4 transform, glm::vec3 color);
    static GameObject constructRectangle(std::vector<Vertex> vertices, CollisionType collisiontype, uint32_t& offSet, glm::mat4 transform, glm::vec3 color);
    
public:
    static std::vector<std::vector<glm::vec3>> generate_grid(int x, int y, float cellsize, glm::vec3 origin);
   
    static void generateGrid(std::vector<GameObject>& gameObjects, std::vector<std::vector<glm::vec3>>& grid, float cellsize, uint32_t& offSet, glm::mat4 transform, glm::vec3 color);
    static void creatSquare(std::vector<GameObject>& gameObjects, glm::vec3 origin, float size, uint32_t& offSet, glm::mat4 transform, glm::vec3 color);

    static void createRectangle(std::vector<GameObject>& gameObjects, glm::vec3 origin, float width, float height, uint32_t& offSet, glm::mat4 transform, glm::vec3 color);
    static void Grid::createRectangle(std::vector<GameObject>& gameObjects, std::vector<Vertex> vertices, uint32_t& offSet, glm::mat4 transform, glm::vec3 color);
   };