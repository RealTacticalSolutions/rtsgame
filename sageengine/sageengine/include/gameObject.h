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

	// Function to rotate the object around a specified axis
	void Rotate(float angle, const glm::vec3& axis)
	{
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, axis);
		properties.transform = rotation * properties.transform;
		upVector = glm::mat3(rotation) * upVector;
		rightVector = glm::mat3(rotation) * rightVector;
	}

	// Function to scale the object uniformly
	void Scale(float scaleFactor)
	{
		scale *= scaleFactor;
	}

	// Function to set the up vector
	void SetUpVector(const glm::vec3& upVec)
	{
		upVector = glm::normalize(upVec);
		rightVector = glm::normalize(glm::cross(glm::vec3(properties.transform[0]), upVector));
	}

	// Function to set the right vector
	void SetRightVector(const glm::vec3& rightVec)
	{
		rightVector = glm::normalize(rightVec);
		upVector = glm::normalize(glm::cross(rightVector, glm::vec3(properties.transform[2])));
	}

	// Function to set the scale
	void SetScale(const glm::vec3& newScale)
	{
		scale = newScale;
	}

	// Function to get the forward vector
	glm::vec3 GetForwardVector() const
	{
		return -glm::vec3(properties.transform[2]);
	}
	
	
private:


};