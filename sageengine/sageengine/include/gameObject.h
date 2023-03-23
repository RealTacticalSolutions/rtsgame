#pragma once

class GameObject
{
public:
	RenderObject* renderObject;
	Properties properties;
	int instanceId = -1;


	GameObject(RenderObject* renderObject, glm::mat4 transform, glm::vec3 color) : renderObject(renderObject), properties{transform, color} {

		
	};

	GameObject(RenderObject* renderObject, glm::mat4 transform, glm::vec3 color, char* texture) : renderObject(renderObject), properties{ transform, color } {

	};

	
private:

};