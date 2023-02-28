#pragma once

class Camera{

public:
	glm::vec3 position;
	glm::vec3 lookPosition;
	glm::vec3 upPosition;
	
	float fov;
	float aspectRatio;
	float nearClippingPlane;
	float farClippingPlane;

	Camera(glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upPosition, float fov, float nearClippingPlane, float farClippingPlane) : position(position), lookPosition(lookPosition),
		upPosition(upPosition), fov(fov), aspectRatio(aspectRatio), nearClippingPlane(nearClippingPlane), farClippingPlane(farClippingPlane) {
		aspectRatio = 0.0f;
	};

	glm::mat4 getView();

	glm::mat4 getProjection();
};