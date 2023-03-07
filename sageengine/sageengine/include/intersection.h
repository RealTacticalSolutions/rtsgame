<<<<<<< HEAD
#pragma once

=======
#pragma once 
>>>>>>> b6da4cd7a57b629668732f51f4d5d871b4c6a246

class Intersection
{
private:
<<<<<<< HEAD
	static bool rectanglesIntersect(const std::vector<Vertex> rect1, const std::vector<Vertex> rect2);
	static std::vector<Vertex> getIntersectionVertices(const std::vector<Vertex>& rect1, const std::vector<Vertex>& rect2);
	
public:
	static bool intersection(GameObject& a, GameObject& b);
	static void intersectionRectangle(std::vector<GameObject>& gameObjects, uint32_t offSet, GameObject& a, GameObject& b);
=======
	static std::vector<glm::vec3> getTransformVertices(std::vector<Vertex> vertices, glm::mat4 transform);
	static bool Intersection::checkSquareIntersection(const std::vector<glm::vec3>& vertices1, const std::vector<glm::vec3>& vertices2);
public:

	static bool intersectSquares(GameObject& square1, GameObject& square2);
>>>>>>> b6da4cd7a57b629668732f51f4d5d871b4c6a246
};