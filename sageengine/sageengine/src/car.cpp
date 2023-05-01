#include "pch.h"
#include "car.h"
#include "waypoints.h"

int Car::getWayPointSize()
{
	return this->waypoints->getSize();
}

WayPoints* Car::getWayPoints()
{
	return this->waypoints;
}

int Car::getCurrentWayPoint()
{
	return this->currentwaypoint;
}

void Car::setCurrentWayPoint(int waypoint)
{
	this->currentwaypoint = waypoint;
}

void Car::setWayPoint(WayPoints* newwaypoints)
{
	this->waypoints = newwaypoints;
	this->currentwaypoint = 0;
}