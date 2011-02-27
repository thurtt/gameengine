/*
 *  dude.cpp
 *  gltest
 *
 *  Created by tom on 2/17/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "dude.h"
#include "rotation.h"
#include <math.h>

bool Dude::close_enough( const point & point1, const point & point2 )
{
	return( point2.x <= point1.x + 5 && point2.x >= point1.x - 5
		   && point2.y <= point1.y + 5 && point2.y >= point1.y - 5 );
}

void Dude::move( float delta )
{
	float rad_angle = atan2( ( _target.y - _y ), ( _target.x - _x ) );
	_angle = -toDegrees( rad_angle );
	
	_x = _x + delta * cos( rad_angle );		
	_y = _y + delta * sin( rad_angle );
	
}

point Dude::dispToWorld( float x, float y )
{
	float offset_x = _x - disp_x;
	float offset_y = _y - disp_y;
	
	return point( offset_x + x, offset_y + y );
}

point Dude::worldToDisp( float x, float y )
{
	float offset_x = _x - disp_x;
	float offset_y = _y - disp_y;
	
	return point( x - offset_x, y - offset_y );
	
}

void Dude::captured(){
}