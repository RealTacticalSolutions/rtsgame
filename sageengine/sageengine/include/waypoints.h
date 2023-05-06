#pragma once


class WayPoints
{
private:
	std::vector<WayPoint> waypoints;
	std::string trafficlight;
public:
	WayPoints(std::vector<WayPoint> waypoints, std::string trafficlight = "-1") : waypoints(waypoints), trafficlight(trafficlight)
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
	std::string getTrafficLightId() const;
	WayPointType getEnum(int index);
};