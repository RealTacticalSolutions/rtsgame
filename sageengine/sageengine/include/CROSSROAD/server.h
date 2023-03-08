#pragma once


class server {
private:
	std::vector<trafficStatusObject> message;
	const char* PORT;
	void server::to_json_traffic(nlohmann::json& j, const std::vector<trafficStatusObject>& objects);
	void server::to_json_message(nlohmann::json& j, const std::vector<messageObject>& objects);
public:
	server(char* port) : PORT(port)
	{
	}
	void startServer();
};