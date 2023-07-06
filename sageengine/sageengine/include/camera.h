#pragma once

class Camera {

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

	/*
	 * @brief Sets the position of a Camera instance.
	 *
	 * @param pos The position to set the camera to.
	 */
	void setPosition(glm::vec3 pos);

	/*
	 * @brief Returns the direction vector of the camera.
	 *
	 * @return The direction vector of the camera.
	 */
	glm::vec3 getDirection();

	/*
	 * @brief Returns the right vector of the camera.
	 *
	 * @return The right vector of the camera.
	 */
	glm::vec3 getRightVector();

	/*
	 * @brief Sets the position and up position of the camera to look at a specified point.
	 *
	 * @param pos    The position to look at.
	 * @param upPos  The up position of the camera.
	 */
	void setLookPosition(glm::vec3 pos, glm::vec3 upPos);

	/*
	 * @brief Rotates the camera around its current position.
	 *
	 * @param degrees The angle to rotate the camera in degrees.
	 */
	void rotateCamera(float degrees);

	/*
	 * @brief Returns the view matrix of the camera.
	 *
	 * @return The view matrix of the camera.
	 */
	glm::mat4 getView();

	/*
	 * @brief Returns the projection matrix of the camera.
	 *
	 * @return The projection matrix of the camera.
	 */
	glm::mat4 getProjection();

	/*
	 * @brief Rotates the camera around a specified point.
	 *
	 * @param yawAngle   The yaw angle to rotate the camera in degrees.
	 * @param pitchAngle The pitch angle to rotate the camera in degrees.
	 * @param up         The up vector of the camera.
	 */
	void rotateAround(float yawAngle, float pitchAngle, const glm::vec3& up);

	/*
	 * @brief Moves the camera's look-at position based on cursor movement.
	 *
	 * @param cursorDelta  The change in cursor position.
	 * @param sensitivity  The sensitivity of the camera movement.
	 */
	void moveLookAt(glm::vec2 cursorDelta, float sensitivity);

	/*
	 * @brief Returns the position of the camera.
	 *
	 * @return The position of the camera.
	 */
	glm::vec3 getPosition();

	/*
	 * @brief Returns the look-at position of the camera.
	 *
	 * @return The look-at position of the camera.
	 */
	glm::vec3 getLookPosition();

	/*
	 * @brief Returns the up vector of the camera.
	 *
	 * @return The up vector of the camera.
	 */
	glm::vec3 getUpVector();

	/*
	 * @brief Returns the forward vector of the camera.
	 *
	 * @return The forward vector of the camera.
	 */
	glm::vec3 getForwardVector();

	/*
	 * @brief Moves the camera in a specified direction in its local space.
	 *
	 * @param deltaTime The time since the last frame update.
	 * @param speed     The movement speed of the camera.
	 */
	void moveForward(float deltaTime, float speed);
	void moveBackward(float deltaTime, float speed);
	void moveLeft(float deltaTime, float speed);
	void moveRight(float deltaTime, float speed);
};