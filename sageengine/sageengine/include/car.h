#pragma once

class Car : public GameObject
{
public:
	Car(RenderObject* renderObject, glm::mat4 transform, glm::vec3 color, int instanceId, WayPoints* waypoints, int currentwaypoint = -1, glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f)) : GameObject(renderObject, transform, color, instanceId, scale), waypoints(waypoints), currentwaypoint(currentwaypoint)
	{
		//std::cout << "Created car with " << waypoints->getSize() << " waypoints and current waypoint " << currentwaypoint << std::endl;
	}
	~Car() override {}

	int getWayPointSize();
	WayPoints* getWayPoints();
	int getCurrentWayPoint();
	void setCurrentWayPoint(int waypoint);

	void setWayPoint(WayPoints* newwaypoints);
	bool weightadded = false;
private:
	WayPoints* waypoints;
	int currentwaypoint;
	
};