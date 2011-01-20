/*
 *  guard.cpp
 *  gltest
 *
 *  Created by tom on 1/15/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "guard.h"
#include "los.h"

Guard::Guard( float start_x, float start_y ) :
	_upCount(0),
	_downCount(MAX_DOWN),
	_rightCount(MAX_RIGHT),
	_leftCount(MAX_LEFT),
	_los(0)
{
	// do some basic setup
	_x = start_x;
	_y = start_y;
	width = 32;
	height = 32;
	texture = LoadTexture( "guard.png" );
	textures.push_back( texture );
	use_los = true;
	
	_los = new line_of_sight( FIELD_OF_VISION, DEPTH_OF_VISION );
	setDrawable( _los );
	
}

Guard::~Guard()
{
	// this is a wee bit dangerous
	delete _los;
	_los = 0;
}
void Guard::movement()
{

	// This is a square roaming pattern	
	if ( _upCount < MAX_UP )
	{
		up();
		if ( _upCount >= MAX_UP )
		{
			_rightCount = 0;
			_angle = 90.0;
		}
	}
	else if ( _rightCount < MAX_RIGHT )
	{
		right();
		if ( _rightCount >= MAX_RIGHT )
		{
			_downCount = 0;
			_angle = 180.0;
		}
	}
	else if ( _downCount < MAX_DOWN )
	{
		down();
		if ( _downCount >= MAX_DOWN )
		{
			_leftCount = 0;
			_angle = -90.0;
		}
	}
	else if ( _leftCount < MAX_LEFT )
	{
		left();
		if ( _leftCount >= MAX_LEFT )
		{
			_upCount =  0;
			_angle = 0.0;
		}
	}	
}

void Guard::up()
{
	_y += DELTA;
	_upCount++;

}
void Guard::down()
{
	_y -= DELTA;
	_downCount++;
}
void Guard::right()
{
	_x += DELTA;
	_rightCount++;
}
void Guard::left()
{
	_x -= DELTA;
	_leftCount++;
}