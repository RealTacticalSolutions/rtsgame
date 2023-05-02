#pragma once

enum Color
{
	RED,
	ORANGE,
	GREEN
};


static glm::vec3 getColor(Color& color)
{

	switch (color)
	{
		case RED: 
			return glm::vec3(1.0f,0.0f,0.0f);
		case ORANGE:
			return glm::vec3(1.0f, 0.5f, 0.0f);
		case GREEN: 
			return glm::vec3(0.0f, 1.0f, 0.0f);
		
	}
};

static glm::vec3 getColor(int color)
{
	int c = color;
	switch (c)
	{
	case 0:
		return glm::vec3(1.0f, 0.0f, 0.0f);
	case 1:
		return glm::vec3(0.0f, 1.0f, 0.0f);
	case 2:
		return glm::vec3(1.0f, 0.5f, 0.0f);
	}
};

static int getId(std::vector<TrafficLight>& lights, const std::string& id)
{
	for (size_t i = 0; i < lights.size(); i++)
	{
		if (lights[i].id == id) 
		{
			return lights[i].index;
		}
	}
	return -1;
};

static int getLightIndex(std::vector<TrafficLight>& lights, const std::string& id)
{
	for (size_t i = 0; i < lights.size(); i++)
	{
		if (lights[i].id == id)
		{
			return i;
		}
	}
	return -1;
};
