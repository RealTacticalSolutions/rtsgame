#include "pch.h"

#define PI 3.14159265

glm::vec3 GameMath::windowToWorldPos(glm::vec2 windowPosition, glm::vec2 windowSize, Camera camera)
{
	float nearClippingOffset = camera.nearClippingPlane + 0.0001f;

	float halfX = windowSize.x / 2;
	float halfY = windowSize.y / 2;

	float tangent = tan(camera.fov / 2);

	float lengthX = camera.aspectRatio * camera.nearClippingPlane * tangent;
	float lengthY = camera.nearClippingPlane * tangent;

	if (windowPosition.x < halfX) {
		lengthX = (windowPosition.x - halfX) / halfX * lengthX;
	}
	else {
		windowPosition.x -= halfX;
		lengthX = windowPosition.x / halfX * lengthX;
	}
	if (windowPosition.y < halfY) {
		windowPosition.y -= halfY;
		lengthY = windowPosition.y / halfY * lengthY * -1;
	}
	else {
		windowPosition.y -= halfY;
		lengthY = (windowPosition.y) / halfY * lengthY * -1;
	}

	glm::vec3 directionVec = glm::normalize(camera.lookPosition - camera.position);
	glm::vec3 up = glm::normalize(camera.upPosition);
	glm::vec3 right = glm::normalize(glm::cross(directionVec, up));

	glm::vec3 nearPlaneCenter = camera.position + (directionVec * nearClippingOffset);

	glm::vec3 firstPos = nearPlaneCenter + (up * lengthY);
	glm::vec3 finalPos = firstPos + (right * lengthX);

	return finalPos;
}
