/*
 *  guard.h
 *  gltest
 *
 *  Created by tom on 1/15/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _GUARD_H_
#define _GUARD_H_

#include "sprite.h"

const unsigned long MAX_UP = 300;
const unsigned long MAX_DOWN = 300;
const unsigned long MAX_RIGHT = 400;
const unsigned long MAX_LEFT = 300;
const float DELTA = 0.8;

const float FIELD_OF_VISION = 180.0;
const float DEPTH_OF_VISION = 250.0;



class Guard : public game_sprite
{
public:
	Guard( float start_x, float start_y );
	~Guard();
	virtual void movement();	
	
private:
	unsigned long _upCount;
	unsigned long _downCount;
	unsigned long _rightCount;
	unsigned long _leftCount;
	drawable * _los;
	
	void up();
	void down();
	void right();
	void left();
	
	
};

#endif // _GUARD_H_

