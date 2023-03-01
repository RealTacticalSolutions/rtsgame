#pragma once


class server {
private:
	std::vector<messageObject>& message;
	const char* PORT;

public:
	server(char* port, std::vector<messageObject>& message) : PORT(port), message(message)
	{
	}
	void startServer();
};