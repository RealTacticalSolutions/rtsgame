#include "pch.h"
#include "waypoints.h"


int WayPoints::getSize() 
{
	return this->waypoints.size();
}
glm::vec3 WayPoints::getWayPointPosition(int index)
{
	if (!(waypoints.size() < 1))
	{
		return waypoints[index].getWayPoint();
	}
	else
	{
		throw std::runtime_error("Waypoint index must be not < 1");
	}
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
	if (!(positions.size() < 1))
	{
		for (size_t i = 0; i < positions.size(); i++)
		{
			this->waypoints.push_back(positions[i]);
		}
	}
	else
	{
		throw std::runtime_error("Waypoint index must be not < 1");
	}
}
std::string WayPoints::getLightId(int index)
{
	return waypoints[index].getLightId();

}

std::string WayPoints::getTrafficLightId() const
{
	return trafficlight;

}

WayPointType WayPoints::getEnum(int index)
{
	return waypoints[index].getEnum();
}