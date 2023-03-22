#pragma once

class GameObject
{
public:
	const Mesh mesh;
	char* texture;
	Properties properties;
	int instanceId = -1;
	int renderObjectIndex = -1;


	GameObject(Mesh mesh, glm::mat4 transform, glm::vec3 color) : mesh(mesh), properties{transform, color} {
		texture = "../../../textures/default.png";
		
	};

	GameObject(Mesh mesh, glm::mat4 transform, glm::vec3 color, char* texture) : mesh(mesh), properties{ transform, color }, texture(texture) {

	};

	
private:

};