/*
 *  rotation.cpp
 *  gltest
 *
 *  Created by tom on 1/30/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "rotation.h"
#define _USE_MATH_DEFINES
#include <math.h>

point rotate( float point_x, float point_y, float orig_x, float orig_y, float angle )
{
	// DANGER: Math zone
	// convert degrees to radians
	float rad_angle = toRadians( -angle );
	
	// the trig identities used for rotation
	float x_prime = orig_x + ( ( ( point_x - orig_x ) * cos( rad_angle ) ) - ( ( point_y - orig_y ) * sin( rad_angle ) ) );
	float y_prime = orig_y + ( ( ( point_x - orig_x ) * sin( rad_angle ) ) + ( ( point_y - orig_y ) * cos( rad_angle ) ) );
	
	// End of DANGER
	return point( x_prime, y_prime );
}

float toDegrees( float radians )
{
	return ( radians * 180 ) / M_PI;

}
float toRadians( float degrees )
{
	return ( degrees * M_PI ) / 180.0;	
}