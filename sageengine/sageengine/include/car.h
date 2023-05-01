#pragma once

class Car : public GameObject
{
public:
	Car(RenderObject* renderObject, glm::mat4 transform, glm::vec3 color, int instanceId, WayPoints* waypoints, int currentwaypoint = -1) : GameObject(renderObject, transform, color, instanceId), waypoints(waypoints), currentwaypoint(currentwaypoint)
	{
		std::cout << "Created car with " << waypoints->getSize() << " waypoints and current waypoint " << currentwaypoint << std::endl;
	}
	~Car() override {}

	int getWayPointSize();
	WayPoints* getWayPoints();
	int getCurrentWayPoint();
	void setCurrentWayPoint(int waypoint);

	void setWayPoint(WayPoints* newwaypoints);
private:
	WayPoints* waypoints;
	int currentwaypoint;
	
};