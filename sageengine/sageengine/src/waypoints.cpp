#include "pch.h"
#include "waypoints.h"


int WayPoints::getSize() 
{
	return this->waypoints.size();
}

int WayPoints::getCurrentWayPoint()
{
	return this->currentwaypoint;
}
int WayPoints::setCurrentWayPoint(int index)
{
	return this->currentwaypoint = index;
}

glm::vec3 WayPoints::getWayPoint(int index)
{
	return this->waypoints[index];
}