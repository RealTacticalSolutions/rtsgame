#pragma once


class WayPoints
{
private:
	std::vector<glm::vec3> waypoints;
	int currentwaypoint = 0;
public:
	WayPoints(std::vector<glm::vec3> waypoints) : waypoints(waypoints)
	{

	}
	WayPoints()
	{

	}
	~WayPoints()
	{
	}

	int getSize();
	int getCurrentWayPoint();
	int setCurrentWayPoint(int index);
	glm::vec3 WayPoints::getWayPoint(int index);
};