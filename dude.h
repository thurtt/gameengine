/*
 *  dude.h
 *  gltest
 *
 *  Created by tom on 2/17/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _DUDE_H_
#define _DUDE_H_

#include "sprite.h"
#include "waypoints.h"
#include "line.h"

class Dude : public game_sprite
{
public:
	waypoint_manager _wpmgr;
	Dude() : _target(0, 0){} 
	point dispToWorld( float x, float y );
	point worldToDisp( float x, float y );
protected:
	point _target;
	bool close_enough( const point & point1, const point & point2 );
	void move( float delta );

private:

};

#endif // _DUDE_H_