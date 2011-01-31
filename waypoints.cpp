/*
 *  waypoints.cpp
 *  gltest
 *
 *  Created by tom on 1/30/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "waypoints.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <math.h>

waypoint_manager::waypoint_manager()
{
	// this is a terrible rng
	srand ( time(NULL) );
}
point waypoint_manager::getNextWaypoint()
{
	if( _index == _waypoints.size() )
	{
		_index = 0;
	}
	return _waypoints[_index++];
}

point waypoint_manager::getRandomWaypoint()
{
	size_t randIndex = rand() % _waypoints.size();
	return _waypoints[randIndex];
}

point waypoint_manager::getClosestWaypoint( point refPoint )
{
	point lowest_point( 0, 0 );
	float lowest_distance = 0;
	float dist = 0;
	
	for( int i = 0; i < _waypoints.size(); i++ )
	{
		dist = sqrt( pow( (refPoint.x - _waypoints[i].x), 2 ) + pow( (refPoint.y - _waypoints[i].y), 2 ) );
		if ( dist < lowest_distance || i == 0 )
		{
			lowest_distance = dist;
			lowest_point = _waypoints[i];
		}
	}
	return lowest_point;
}

void waypoint_manager::reset()
{
	_index = 0;
}
void waypoint_manager::addWaypoint( point newPoint )
{
	_waypoints.push_back( newPoint );
}

bool waypoint_manager::removeWaypoint( point waypoint )
{
	std::vector<point>::iterator itr = find( _waypoints.begin(), _waypoints.end(), waypoint );
	if( itr == _waypoints.end() )
	{
		return false;
	}
	_waypoints.erase( itr );
	return false;
}