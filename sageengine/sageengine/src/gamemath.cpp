#include "pch.h"

#define PI 3.14159265

glm::vec3 GameMath::windowToWorldPos(glm::vec2 windowPosition, Camera camera)
{
	float xAngle = atan(camera.aspectRatio);
	double yAngle = atan(1 / camera.aspectRatio) * 180 / PI;
	glm::vec3 directionVec = glm::normalize(camera.lookPosition - camera.position);
	glm::vec3 up = glm::normalize(camera.upPosition);
	glm::vec3 right = glm::normalize(glm::cross(directionVec, up));

	glm::vec3 nearPlaneCenter = camera.position + (directionVec * camera.nearClippingPlane);

	glm::vec3 topPos = nearPlaneCenter + (up * camera.nearClippingPlane * camera.aspectRatio);
	glm::vec3 rightPos = nearPlaneCenter + (right * camera.nearClippingPlane * camera.aspectRatio);

	



	std::cout << "Pos X: " << topPos.x << " Pos Y: " << topPos.y << " Pos Z: " << topPos.z << std::endl;
	return glm::vec3(1.0f);
}
