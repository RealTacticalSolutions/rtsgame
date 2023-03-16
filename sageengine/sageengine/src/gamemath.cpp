#include "pch.h"

#define PI 3.14159265

glm::vec3 GameMath::windowToWorldPos(glm::vec2 windowPosition, glm::vec2 windowSize, Camera camera)
{

	float halfX = windowSize.x / 2;
	float halfY = windowSize.y / 2;

	float lengthX = camera.aspectRatio * camera.nearClippingPlane;
	float lengthY = 1 / camera.aspectRatio * camera.nearClippingPlane;

	if (windowPosition.x < halfX) {
		lengthX = (windowPosition.x - halfX) / halfX * lengthX;
	}
	else {
		windowPosition.x -= halfX;
		lengthX = windowPosition.x / halfX * lengthX;
	}
	if (windowPosition.y < halfY) {
		lengthY = (windowPosition.y - halfY) / halfY * lengthY;
	}
	else {
		windowPosition.y -= halfY;
		lengthY = windowPosition.y / halfY * lengthY;
	}

	glm::vec3 directionVec = glm::normalize(camera.lookPosition - camera.position);
	glm::vec3 up = glm::normalize(camera.upPosition);
	glm::vec3 right = glm::normalize(glm::cross(directionVec, up));

	glm::vec3 nearPlaneCenter = camera.position + (directionVec * camera.nearClippingPlane);

	glm::vec3 firstPos = nearPlaneCenter + (up * lengthY);
	glm::vec3 finalPos = firstPos + (right * lengthX);

	std::cout << "Pos X: " << finalPos.x << " Pos Y: " << finalPos.y << " Pos Z: " << finalPos.z << std::endl;
	return glm::vec3(1.0f);
}
