#pragma once

class TrafficLight;

class server {
private:
	std::vector<trafficStatusObject> message;
	std::vector<TrafficLight>& lights;
	const char* PORT;
	void server::to_json_traffic(nlohmann::json& j, const std::vector<trafficStatusObject>& objects);
	void server::to_json_message(nlohmann::json& j, const std::vector<messageObject>& objects);
public:
	server(char* port, std::vector<TrafficLight>& lights) : PORT(port), lights(lights)
	{
	}
	void startServer();
};