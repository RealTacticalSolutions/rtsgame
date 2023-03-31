#pragma once

class WayPoint
{
private:
	glm::vec3 position;
	std::string lightid;
	
public:
	WayPoint(glm::vec3 position, std::string lightid = "-1") : position(position), lightid(lightid)
	{
	}
	glm::vec3 getWayPoint();
	std::string getLightId();
};