#include "pch.h"
#include "waypoint.h"


glm::vec3 WayPoint::getWayPoint()
{
	return this->position;
}

std::string WayPoint::getLightId()
{
	return this->lightid;
}

WayPointType WayPoint::getEnum()
{
	return this->type;
}

WayPoints* WayPoint::getNewPath(int index)
{
	return paths[index];
}