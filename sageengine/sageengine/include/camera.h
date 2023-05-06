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
		lookPosition += position;
	}

	glm::vec3 getDirection();
	glm::vec3 getRightVector();

	void setLookPosition(glm::vec3 pos, glm::vec3 upPos) {
		lookPosition = glm::normalize(pos - position);
		upPosition = upPos;
	}

	void rotateCamera(float degrees) {
		glm::vec3 direction = glm::normalize(lookPosition - position);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), direction);
		upPosition = glm::vec3(glm::vec4(upPosition, 0.0f) * rotationMatrix);
	}

	glm::mat4 getView();

	glm::mat4 getProjection();

	void rotateAround(float yawAngle, float pitchAngle, const glm::vec3& up);
	
	void moveLookAt(glm::vec2 cursorDelta, float sensitivity);

	glm::vec3 getPosition();

	glm::vec3 getLookPosition();

	glm::vec3 getUpVector();

	glm::vec3 getForwardVector() {
		return glm::normalize(lookPosition - position);
	}

	// Move the camera forward
	void moveForward(float deltaTime, float speed)
	{
		position += speed * deltaTime * getForwardVector();
	}

	// Move the camera backward
	void moveBackward(float deltaTime, float speed)
	{
		position -= speed * deltaTime * getForwardVector();
	}

	// Move the camera left
	void Camera::moveLeft(float deltaTime, float speed)
	{
		glm::vec3 right = getRightVector();
		position -= speed * deltaTime * right;
		lookPosition -= speed * deltaTime * right;
	}

	// Move the camera right
	void Camera::moveRight(float deltaTime, float speed)
	{
		glm::vec3 right = getRightVector();
		position += speed * deltaTime * right;
		lookPosition += speed * deltaTime * right;
	}

};