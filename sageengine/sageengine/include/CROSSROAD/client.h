#pragma once

class client {
private:
	struct trafficObject {
		int id;
		double weight;
	};
	const char* IP;
	const char* PORT;

	void to_json(nlohmann::json& j, const trafficObject& s);
	void to_json(nlohmann::json& j, const std::vector<trafficObject>& objects);
public:
	client(char* ip, char* port) : IP(ip), PORT(port)
	{
	}

	void startClient();

};