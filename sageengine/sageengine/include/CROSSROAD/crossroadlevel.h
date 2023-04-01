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
	std::vector<std::unique_ptr<GameObject>>& gameObjects_ref;
	std::vector<TrafficLight>& lights;
	void updateColor(int index, glm::vec3 color);
public:
	CrossRoadLevel(std::vector<messageObject>& message_input, std::vector<std::unique_ptr<GameObject>>& gameObjects_input, std::vector<TrafficLight>& lights) : message_ref(message_input), gameObjects_ref(gameObjects_input), lights(lights)
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