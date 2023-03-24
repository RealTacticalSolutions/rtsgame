#pragma once


class WayPoints
{
private:
	std::vector<glm::vec3> waypoints;
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
	glm::vec3 WayPoints::getWayPoint(int index);
};