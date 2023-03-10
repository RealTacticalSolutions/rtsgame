#pragma once 

class Intersection
{
private:
	static std::vector<glm::vec3> getTransformVertices(std::vector<Vertex> vertices, glm::mat4 transform);
	static bool Intersection::checkSquareIntersection(const std::vector<glm::vec3>& vertices1, const std::vector<glm::vec3>& vertices2);
public:

	static bool intersectSquares(GameObject& square1, GameObject& square2);
};