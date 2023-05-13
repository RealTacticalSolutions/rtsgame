#pragma once

class TrafficLight;
class TimerObject;

class client {
private:

	const char* IP;
	const char* PORT;
	std::vector<messageObject>& message;
	TimerObject& timer;
	std::vector<TrafficLight>& lights;
	void to_json(nlohmann::json& j, const messageObject& s);
	void to_json_message(nlohmann::json& j, const std::vector<messageObject>& objects);
	void to_json_traffic(nlohmann::json& j, const std::vector<trafficStatusObject>& objects);
public:
	client(char* ip, char* port, std::vector<messageObject>& message, TimerObject& timer, std::vector<TrafficLight>& lights) : IP(ip), PORT(port), message(message), timer(timer), lights(lights)
	{
	}

	void startClient();

};