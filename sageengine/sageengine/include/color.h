#pragma once

enum Color
{
	RED,
	GREEN,
	ORANGE
};

static glm::vec3 getColor(Color color)
{
	Color c = color;
	switch (c)
	{
		case RED: 
			return glm::vec3(1.0f,0.0f,0.0f);
		case GREEN: 
			return glm::vec3(0.0f, 1.0f, 0.0f);
		case ORANGE:
			return glm::vec3(1.0f, 0.5f, 0.0f);
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
