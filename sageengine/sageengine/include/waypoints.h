#pragma once


class WayPoints
{
private:
	std::vector<WayPoint> waypoints;
	
public:
	WayPoints(std::vector<WayPoint> waypoints) : waypoints(waypoints)
	{

	}
	WayPoints()
	{

	}
	~WayPoints()
	{
	}

	int getSize();
	glm::vec3 getWayPointPosition(int index);
	WayPoint getWayPoint(int index);
	void addWayPoint(WayPoint pos);
	void addWayPoints(std::vector<WayPoint> positions);
	std::string getLightId(int index);
};