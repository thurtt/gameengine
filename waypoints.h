/*
 *  waypoints.h
 *  gltest
 *
 *  Created by tom on 1/30/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "line.h"

class waypoint_manager
{
public:
	waypoint_manager();
	point getNextWaypoint();
	point popNextWaypoint();
	point getRandomWaypoint();
	point getClosestWaypoint( point refPoint );
	void reset();
	void addWaypoint( point newPoint );
	bool removeWaypoint( point waypoint );
	int getWaypointCount();
	
private:
	
	std::vector<point> _waypoints;
	size_t _index;
	
};