#include "pch.h"
#include "waypoints.h"


int WayPoints::getSize() 
{
	return this->waypoints.size();
}
glm::vec3 WayPoints::getWayPoint(int index)
{
	return this->waypoints[index];
}