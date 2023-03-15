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

static int getId(const double& id)
{
	if (id == 5.1) {
		return 1;
	}
	else if (id == 2.1) {
		return 2;
	}
	else if (id == 11.1) {
		return 3;
	}
	else if (id == 8.1) {
		return 4;
	}
	else {
		return -1;
	}
};
