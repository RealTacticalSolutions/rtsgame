#include "pch.h"
#include "train.h"
#include "waypoints.h"

int Train::getWayPointSize()
{
	return this->waypoints->getSize();
}

WayPoints* Train::getWayPoints()
{
	return this->waypoints;
}

int Train::getCurrentWayPoint()
{
	return this->currentwaypoint;
}

void Train::setCurrentWayPoint(int waypoint)
{
	this->currentwaypoint = waypoint;
}

void Train::setWayPoint(WayPoints* newwaypoints)
{
	this->waypoints = newwaypoints;
	this->currentwaypoint = 0;
}