#pragma once

class GameObject
{
public:
	
	RenderObject* renderObject;
	Properties properties;
	glm::vec3 upVector;
	glm::vec3 rightVector;
	glm::vec3 scale;
	int instanceId;

	GameObject(RenderObject* renderObject, glm::mat4 transform, glm::vec3 color, int instanceId = -1, glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f)) : renderObject(renderObject), properties{transform, color}, instanceId(instanceId) , scale(scale)
	{

		
	}
	virtual ~GameObject() 
	{
	}

	/*
	* @brief Rotates the game object around a specified axis.
	 *
	* @param angle The angle of rotation in degrees.
	* @param axis  The axis of rotation specified as a glm::vec3.
	*/
	void Rotate(float angle, const glm::vec3& axis);

	/*
	 * @brief Scales the game object by a specified factor.
	 *
	 * @param scaleFactor The scaling factor to apply to the game object.
	 */
	void Scale(float scaleFactor);

	/*
	 * @brief Sets the up vector of the game object.
	 *
	 * @param upVec The new up vector to set for the game object.
	 */
	void SetUpVector(const glm::vec3& upVec);

	/*
	 * @brief Sets the right vector of the game object.
	 *
	 * @param rightVec The new right vector to set for the game object.
	 */
	void SetRightVector(const glm::vec3& rightVec);

	/*
	 * @brief Sets the scale of the game object.
	 *
	 * @param newScale The new scale to set for the game object.
	 */
	void SetScale(const glm::vec3& newScale);

	/*
	 * @brief Returns the forward vector of the game object.
	 *
	 * @return The forward vector of the game object.
	 */
	glm::vec3 GetForwardVector() const;
	
private:


};