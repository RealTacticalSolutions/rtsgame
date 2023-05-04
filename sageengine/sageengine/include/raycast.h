struct RayCast {
	glm::vec3 origin;
	alignas(16) glm::vec3 direction;
};

struct RayResult {
	bool hit;
	alignas(16) glm::vec3 intersectionPoint;
};