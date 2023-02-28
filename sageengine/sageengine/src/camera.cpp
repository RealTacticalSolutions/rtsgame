#include "pch.h"

glm::mat4 Camera::getView() {
	return glm::lookAt(position, lookPosition, upPosition);
}

glm::mat4 Camera::getProjection() {

	glm::mat4 temp = glm::perspective(fov, aspectRatio, nearClippingPlane, farClippingPlane);
	temp[1][1] *= -1;
	return temp;
}