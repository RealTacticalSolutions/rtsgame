#pragma once

class GameObject
{
public:
	RenderObject* renderObject;
	Properties properties;
	int instanceId;


	GameObject(RenderObject* renderObject, glm::mat4 transform, glm::vec3 color, int instanceId = -1) : renderObject(renderObject), properties{transform, color}, instanceId(instanceId) {

		
	};
	
private:

};