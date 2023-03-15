#pragma once


class CrossRoadLevel
{
private:
	char* IP;
	char* PORT;
	char* SERVER_PORT;
	client* myClient;
	server* myServer;
	std::thread serverThread;
	std::thread clientThread;

	std::vector<messageObject>& message_ref;
	std::vector<GameObject>& gameObjects_ref;
	void updateColor(int index, glm::vec3 color);
public:
	CrossRoadLevel(std::vector<messageObject>& message_input, std::vector<GameObject>& gameObjects_input) : message_ref(message_input), gameObjects_ref(gameObjects_input)
	{

	}

	~CrossRoadLevel()
	{
		
		delete myClient;
		delete myServer;
	}
	void init();
	void mainLoop();
	void cleanup();
};