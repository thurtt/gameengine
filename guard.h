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
#include "waypoints.h"

const float PATROL_DELTA = 0.5;
const float CHASE_DELTA = 0.9;

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
	~Guard();
	virtual void movement();	
	
private:
	void patrol();
	void chase( point waypoint );
	bool close_enough( const point & point1, const point & point2 );
	void move( float delta );
	line_of_sight * _los;
	Text * _text;
	point _target;

	void checkCaptures();
	bool _chase;
	waypoint_manager _wpmgr;

};

#endif // _GUARD_H_

