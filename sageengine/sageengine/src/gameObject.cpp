#include "pch.h"
#include "gameObject.h"

void GameObject::Rotate(float angle, const glm::vec3& axis)
{
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, axis);
	properties.transform = rotation * properties.transform;
	upVector = glm::mat3(rotation) * upVector;
	rightVector = glm::mat3(rotation) * rightVector;
}

void GameObject::Scale(float scaleFactor)
{
	scale *= scaleFactor;
}

void GameObject::SetUpVector(const glm::vec3& upVec)
{
	upVector = glm::normalize(upVec);
	rightVector = glm::normalize(glm::cross(glm::vec3(properties.transform[0]), upVector));
}

void GameObject::SetRightVector(const glm::vec3& rightVec)
{
	rightVector = glm::normalize(rightVec);
	upVector = glm::normalize(glm::cross(rightVector, glm::vec3(properties.transform[2])));
}

void GameObject::SetScale(const glm::vec3& newScale)
{
	scale = newScale;
}

glm::vec3 GameObject::GetForwardVector() const
{
	return -glm::vec3(properties.transform[2]);
}