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