/*
 *  guard.cpp
 *  gltest
 *
 *  Created by tom on 1/15/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "guard.h"

Guard::Guard( float start_x, float start_y )
{
	// do some basic setup
	_x = start_x;
	_y = start_y;
	width = 32;
	height = 32;
	texture = LoadTexture( "guard.png" );
	textures.push_back( texture );
}

void Guard::RoamForever()
{
	// move up for a while
	
	// move right for a while
	
	
	// move down for a while
	
	// move left for a while
	
	// repeat
}