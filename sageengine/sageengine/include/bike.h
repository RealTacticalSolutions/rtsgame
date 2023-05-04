#pragma once

class Bike : public GameObject
{
public:
	Bike(RenderObject* renderObject, glm::mat4 transform, glm::vec3 color, int instanceId, WayPoints* waypoints, int currentwaypoint = -1) : GameObject(renderObject, transform, color, instanceId), waypoints(waypoints), currentwaypoint(currentwaypoint)
	{
		//std::cout << "Created car with " << waypoints->getSize() << " waypoints and current waypoint " << currentwaypoint << std::endl;
	}

	~Bike() override {}

	int getWayPointSize();
	WayPoints* getWayPoints();
	int getCurrentWayPoint();
	void setCurrentWayPoint(int waypoint);
	WayPointType getEnum();
	void setWayPoint(WayPoints* newwaypoints);
private:
	WayPoints* waypoints;
	int currentwaypoint;

};