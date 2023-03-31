#include "pch.h"
#include "waypoints.h"


int WayPoints::getSize() 
{
	return this->waypoints.size();
}
glm::vec3 WayPoints::getWayPointPosition(int index)
{
	return waypoints[index].getWayPoint();
}
WayPoint WayPoints::getWayPoint(int index)
{
	return waypoints[index];
}


void WayPoints::addWayPoint(WayPoint pos)
{
	this->waypoints.push_back(pos);
}
void WayPoints::addWayPoints(std::vector<WayPoint> positions)
{
	for (size_t i = 0; i < positions.size()-1; i++)
	{
		this->waypoints.push_back(positions[i]);
	}
}
std::string WayPoints::getLightId(int index)
{
	return waypoints[index].getLightId();

}