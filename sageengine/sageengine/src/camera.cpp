#include "pch.h"

void Camera::setPosition(glm::vec3 pos)
{
    position = pos;
    lookPosition += position;
}

void Camera::setLookPosition(glm::vec3 pos, glm::vec3 upPos) {
    lookPosition = glm::normalize(pos - position);
    upPosition = upPos;
}

void Camera::rotateCamera(float degrees) {
    glm::vec3 direction = glm::normalize(lookPosition - position);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), direction);
    upPosition = glm::vec3(glm::vec4(upPosition, 0.0f) * rotationMatrix);
}

glm::mat4 Camera::getView() {
	return glm::lookAt(position, lookPosition, upPosition);
}

glm::mat4 Camera::getProjection() {

	glm::mat4 temp = glm::perspective(fov, aspectRatio, nearClippingPlane, farClippingPlane);
	temp[1][1] *= -1;
	return temp;
}

void Camera::rotateAround(float yawAngle, float pitchAngle, const glm::vec3& up)
{
    glm::vec3 toTarget = lookPosition - position;
    float distance = glm::length(toTarget);

    // Rotate around the up vector
    glm::mat4 yawRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(yawAngle), up);
    glm::vec4 rotatedToTarget = glm::vec4(toTarget, 1.0f) * yawRotationMatrix;
    glm::vec3 newToTarget = glm::vec3(rotatedToTarget);

    // Rotate around the right vector
    glm::vec3 rightVector = glm::normalize(glm::cross(up, newToTarget));
    glm::mat4 pitchRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(pitchAngle), rightVector);
    glm::vec4 rotatedToTarget2 = glm::vec4(newToTarget, 1.0f) * pitchRotationMatrix;
    glm::vec3 newToTarget2 = glm::vec3(rotatedToTarget2);

    //std::cout << getUpVector().x << getUpVector().y << getUpVector().z;
    // Update the camera's position to maintain the same distance to the look-at position
    position = lookPosition - distance * glm::normalize(newToTarget2);
}

void Camera::moveLookAt(glm::vec2 cursorDelta, float sensitivity) 
{
    glm::vec3 upVector = getUpVector();

    // Calculate rotation angles based on deltaX and deltaY
    float yaw = cursorDelta.x * sensitivity;
    float pitch = cursorDelta.y * sensitivity;

    // Update camera orientation
    rotateAround(-yaw, pitch, upVector);

    // Update look at position
    glm::vec3 front = glm::normalize(lookPosition - position);
    lookPosition = position + front;
    upPosition = glm::normalize(glm::cross(getRightVector(), getDirection()));
}

glm::vec3 Camera::getPosition() { return position; }

glm::vec3 Camera::getLookPosition() { return lookPosition; }

glm::vec3 Camera::getUpVector() { return upPosition; }

glm::vec3 Camera::getForwardVector() {  return glm::normalize(lookPosition - position); }

glm::vec3 Camera::getDirection()
{
    return glm::normalize(lookPosition - position);
}

glm::vec3 Camera::getRightVector()
{
    return glm::normalize(glm::cross(getDirection(), upPosition));
}

void Camera::moveForward(float deltaTime, float speed)
{
    position += speed * deltaTime * getForwardVector();
}

void Camera::moveBackward(float deltaTime, float speed)
{
    position -= speed * deltaTime * getForwardVector();
}

void Camera::moveLeft(float deltaTime, float speed)
{
    glm::vec3 right = getRightVector();
    position -= speed * deltaTime * right;
    lookPosition -= speed * deltaTime * right;
}

void Camera::moveRight(float deltaTime, float speed)
{
    glm::vec3 right = getRightVector();
    position += speed * deltaTime * right;
    lookPosition += speed * deltaTime * right;
}