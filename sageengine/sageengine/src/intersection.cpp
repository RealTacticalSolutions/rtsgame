#include "pch.h"
#include "intersection.h"


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
    std::vector<glm::vec3> square1_vertices = getTransformVertices(square1.renderObject->mesh.vertices, square1.properties.transform);
    std::vector<glm::vec3> square2_vertices = getTransformVertices(square2.renderObject->mesh.vertices, square2.properties.transform);

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
