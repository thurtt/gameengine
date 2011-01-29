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
#include "line.h"

const unsigned long MAX_UP = 300;
const unsigned long MAX_DOWN = 300;
const unsigned long MAX_RIGHT = 400;
const unsigned long MAX_LEFT = 300;
const float DELTA = 0.8;

const float FIELD_OF_VISION = 180.0;
const float DEPTH_OF_VISION = 250.0;

const int GUARD_WIDTH = 32;
const int GUARD_HEIGHT = 32;

const char GUARD_IMAGE[10] = "guard.png";

class Text;
class line_of_sight;
class game_sprite;

class Guard : public game_sprite
{
public:
	std::vector<game_sprite*> * _players;
	Guard( float start_x, float start_y, std::vector<game_sprite*> * sprites );
	void setGuardZone( polygon zone ){ _zone = zone;}
	~Guard();
	virtual void movement();	
	
private:
	void patrol();
	void pursue();
	unsigned long _upCount;
	unsigned long _downCount;
	unsigned long _rightCount;
	unsigned long _leftCount;
	line_of_sight * _los;
	Text * _text;
	float _target_x;
	float _target_y;
	float _target_slope;
	float _target_b;

	void up();
	void down();
	void right();
	void left();
	void checkCaptures();
	bool _chase;
	polygon _zone;
};

#endif // _GUARD_H_

