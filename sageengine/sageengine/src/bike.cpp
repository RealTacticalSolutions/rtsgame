#include "pch.h"
#include "bike.h"
#include "waypoints.h"

int Bike::getWayPointSize()
{
	return this->waypoints->getSize();
}

WayPoints* Bike::getWayPoints()
{
	return this->waypoints;
}

int Bike::getCurrentWayPoint()
{
	return this->currentwaypoint;
}

void Bike::setCurrentWayPoint(int waypoint)
{
	this->currentwaypoint = waypoint;
}

void Bike::setWayPoint(WayPoints* newwaypoints)
{
	this->waypoints = newwaypoints;
	this->currentwaypoint = 0;
}