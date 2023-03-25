#pragma once

class TrafficLight
{
	
public:
	TrafficLight(std::string id, int index, double weight = 0, int status = 0): id(id), index(index), weight(weight), status(status)
	{
	}

	std::string id;
	int index;
	double weight;
	int status;
};

