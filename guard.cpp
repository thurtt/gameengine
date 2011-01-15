/*
 *  guard.cpp
 *  gltest
 *
 *  Created by tom on 1/15/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "guard.h"

Guard::Guard( float start_x, float start_y ) :
	_upCount(0),
	_downCount(MAX_DOWN),
	_rightCount(MAX_RIGHT),
	_leftCount(MAX_LEFT)
{
	// do some basic setup
	_x = start_x;
	_y = start_y;
	width = 32;
	height = 32;
	texture = LoadTexture( "guard.png" );
	textures.push_back( texture );
}
void Guard::movement()
{

	// This is a square roaming pattern	
	if ( _upCount < MAX_UP )
	{
		up();
		_rightCount = _upCount >= MAX_UP ? 0 : MAX_RIGHT;
	}
	else if ( _rightCount < MAX_RIGHT )
	{
		right();
		_downCount = _rightCount >= MAX_RIGHT ? 0 : MAX_DOWN;
	}
	else if ( _downCount < MAX_DOWN )
	{
		down();
		_leftCount = _downCount >= MAX_DOWN ? 0 : MAX_LEFT;
	}
	else if ( _leftCount < MAX_LEFT )
	{
		left();
		_upCount = _leftCount >= MAX_LEFT ? 0 : MAX_UP;
	}	
}
void Guard::up()
{
	_x += DELTA;
	_upCount++;

}
void Guard::down()
{
	_x -= DELTA;
	_downCount++;
}
void Guard::right()
{
	_y += DELTA;
	_rightCount++;
}
void Guard::left()
{
	_y -= DELTA;
	_leftCount++;
}