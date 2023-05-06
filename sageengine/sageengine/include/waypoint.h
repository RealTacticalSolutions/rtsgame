#pragma once
#include "waypointType.h"

class WayPoints;

class WayPoint
{
private:
	glm::vec3 position;
	std::string lightid;
	WayPointType type;
	std::vector<WayPoints*> paths;
	
public:
	WayPoint(glm::vec3 position, WayPointType waypointtype = General, std::string lightid = "-1",  std::vector<WayPoints*> paths = {}) : position(position), lightid(lightid), type(waypointtype), paths(paths)
	{
	}
	glm::vec3 getWayPoint();
	std::string getLightId();
	WayPointType getEnum();
	WayPoints* getNewPath(int index);
};