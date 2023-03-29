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
		aspectRatio = 3.0f;
	};

	void setPosition(glm::vec3 pos) {
		position = pos;

		glm::vec3 direction = glm::normalize(lookPosition - position);
		glm::vec3 right = glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)));
		glm::vec3 up = glm::normalize(glm::cross(right, direction));

		upPosition = up;
	}

	void setLookPosition(glm::vec3 pos) {
		lookPosition = pos;
		upPosition = glm::cross(position, lookPosition);
	}

	void rotateCamera(float degrees) {
		glm::vec3 direction = glm::normalize(lookPosition - position);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), direction);
		upPosition = glm::vec3(glm::vec4(upPosition, 0.0f) * rotationMatrix);
	}

	glm::mat4 getView();

	glm::mat4 getProjection();
};