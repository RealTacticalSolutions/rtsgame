#pragma once


class Intersection
{
private:
	static bool rectanglesIntersect(const std::vector<Vertex> rect1, const std::vector<Vertex> rect2);
	static std::vector<Vertex> getIntersectionVertices(const std::vector<Vertex>& rect1, const std::vector<Vertex>& rect2);
	
public:
	static bool intersection(GameObject& a, GameObject& b);
	static void intersectionRectangle(std::vector<GameObject>& gameObjects, uint32_t offSet, GameObject& a, GameObject& b);
};