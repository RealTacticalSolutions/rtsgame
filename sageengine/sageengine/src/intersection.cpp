#include "pch.h"
#include "intersection.h"

<<<<<<< HEAD

/**
* Determines whether two GameObjects intersect by extracting their vertex data and checking
* if their bounding rectangles intersect using the rectanglesIntersect helper function.
* 
* @param a The first GameObject to check for intersection.
* @param b The second GameObject to check for intersection.
* 
* @return true if the bounding rectangles of the GameObjects intersect, false otherwise.
*/
bool Intersection::intersection(GameObject& a, GameObject& b) 
{
    std::vector<Vertex> a_vertices = a.vertices;
    std::vector<Vertex> b_vertices = b.vertices;

    return rectanglesIntersect(a_vertices, b_vertices);
}

/**
* Checks whether two given GameObjects intersect, and creates a new rectangle GameObject representing the intersection if they do. 
* The new rectangle is added to the provided vector of gameObjects using the given offset for indices indexing.
* 
* @param gameObjects The vector of GameObjects to add the new rectangle to.
* @param offSet The offset used for indexing indices.
* @param a The first GameObject to check for intersection.
* @param b The second GameObject to check for intersection.
* 
*/
void Intersection::intersectionRectangle(std::vector<GameObject>& gameObjects, uint32_t offSet, GameObject& a, GameObject& b)
{
    std::vector<Vertex> a_vertices = a.vertices;
    std::vector<Vertex> b_vertices = b.vertices;
    // Todo: implement something for the height (Z) maybe?

    if (rectanglesIntersect(a_vertices, b_vertices))
    {
        Grid::createRectangle(gameObjects,getIntersectionVertices(a_vertices, b_vertices), offSet, glm::mat4(1.0f), glm::vec3(1.0f,0.0f,0.0f));
    }
}

/**
* Calculates the vertices of the intersection of two rectangles.
* Vertices are [0]bottomleft,[1]bottomright,[2]topleft,[3]topright
* The vertices of the intersection are calculated based on the bottom-left and top-right vertices
* of the two rectangles.
*
* @param rect1 The vertices of the first rectangle.
* @param rect2 The vertices of the second rectangle.

* @return true if the rectangles intersect, false otherwise.
*/
bool Intersection::rectanglesIntersect(const std::vector<Vertex> rect1, const std::vector<Vertex> rect2)
{
    // Todo: for some reason if we want to use [2]topleft and [1]bottomright it doenst work. but this does?!
    glm::vec2 min1 = glm::vec2(rect1[0].pos.x, rect1[0].pos.y);
    glm::vec2 max1 = glm::vec2(rect1[3].pos.x, rect1[3].pos.y);
    glm::vec2 min2 = glm::vec2(rect2[0].pos.x, rect2[0].pos.y);
    glm::vec2 max2 = glm::vec2(rect2[3].pos.x, rect2[3].pos.y);

    if (max1.x < min2.x || max2.x < min1.x) {
        return false;
    }

    if (max1.y < min2.y || max2.y < min1.y) {
        return false;
    }

    return true;
}

/**
* Calculates the vertices of the intersection of two rectangles.
* Vertices are [0]bottomleft,[1]bottomright,[2]topleft,[3]topright
* The vertices of the intersection are calculated based on the bottom-left and top-right vertices
* of the two rectangles.
* 
* @param rect1 The vertices of the first rectangle.
* @param rect2 The vertices of the second rectangle.
* 
* @return A vector containing the vertices of the intersection rectangle, same vertices as expected.
*/
std::vector<Vertex> Intersection::getIntersectionVertices(const std::vector<Vertex>& rect1, const std::vector<Vertex>& rect2)
{
    std::vector<Vertex> intersection_vertices;

    glm::vec2 min1 = glm::vec2(rect1[0].pos.x, rect1[0].pos.y);
    glm::vec2 max1 = glm::vec2(rect1[3].pos.x, rect1[3].pos.y);
    glm::vec2 min2 = glm::vec2(rect2[0].pos.x, rect2[0].pos.y);
    glm::vec2 max2 = glm::vec2(rect2[3].pos.x, rect2[3].pos.y);

    if (max1.x < min2.x || max2.x < min1.x || max1.y < min2.y || max2.y < min1.y) {
        // The rectangles don't intersect
        return intersection_vertices;
    }


    glm::vec2 intersection_min(std::max(min1.x, min2.x), std::max(min1.y, min2.y));
    glm::vec2 intersection_max(std::min(max1.x, max2.x), std::min(max1.y, max2.y));

    intersection_vertices.push_back(Vertex{ glm::vec3(intersection_min.x, intersection_min.y, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f) }); // Bottom left
    intersection_vertices.push_back(Vertex{ glm::vec3(intersection_max.x, intersection_min.y, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f) }); // Bottom right
    intersection_vertices.push_back(Vertex{ glm::vec3(intersection_min.x, intersection_max.y, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f) }); // Top left
    intersection_vertices.push_back(Vertex{ glm::vec3(intersection_max.x, intersection_max.y, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f) }); // Top right

    return intersection_vertices;
}

=======
std::vector<glm::vec3> Intersection::getTransformVertices(std::vector<Vertex> vertices, glm::mat4 transform)
{

    std::vector<glm::vec4> vertices4;
    for (int i = 0; i < vertices.size(); i++) {
        vertices4.push_back(glm::vec4(vertices[i].pos, 1.0f));
    }

    for (int i = 0; i < vertices4.size(); i++) {
        vertices4[i] = transform * vertices4[i];
    }

    std::vector<glm::vec3> transformedVertices;
    for (int i = 0; i < vertices4.size(); i++) {
        transformedVertices.push_back(glm::vec3(vertices4[i]));
    }

    return transformedVertices;
}

bool Intersection::intersectSquares(GameObject& square1, GameObject& square2)
{
    std::vector<glm::vec3> square1_vertices = getTransformVertices(square1.vertices, square1.properties.transform);
    std::vector<glm::vec3> square2_vertices = getTransformVertices(square2.vertices, square2.properties.transform);

    return checkSquareIntersection(square1_vertices, square2_vertices);
}

bool Intersection::checkSquareIntersection(const std::vector<glm::vec3>& vertices1, const std::vector<glm::vec3>& vertices2) 
{
    // Check if the squares overlap on the x and y axes

    // Compute the min and max x and y values of the first square
    float minX1 = vertices1[0].x;
    float maxX1 = vertices1[1].x;
    float minY1 = vertices1[0].y;
    float maxY1 = vertices1[2].y;

    // Compute the min and max x and y values of the second square
    float minX2 = vertices2[0].x;
    float maxX2 = vertices2[1].x;
    float minY2 = vertices2[0].y;
    float maxY2 = vertices2[2].y;

    // Check if the squares overlap on the x axis
    if (maxX1 < minX2 || maxX2 < minX1) {
        return false;
    }

    // Check if the squares overlap on the y axis
    if (maxY1 < minY2 || maxY2 < minY1) {
        return false;
    }

    // If both overlap, the squares intersect
    return true;
}
>>>>>>> b6da4cd7a57b629668732f51f4d5d871b4c6a246
