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

#include "dude.h"
#include "line.h"
#include "game_map.h"

const float PATROL_DELTA = 0.5;
const float CHASE_DELTA = 0.8;

const float FIELD_OF_VISION = 180.0;
const float DEPTH_OF_VISION = 250.0;

const int GUARD_WIDTH = 32;
const int GUARD_HEIGHT = 32;

const char GUARD_IMAGE[10] = "guard.png";

class Text;
class line_of_sight;
class game_sprite;

class Guard : public Dude
{
public:
	std::vector<game_sprite*> * _players;
	Guard( float start_x, float start_y, std::vector<game_sprite*> * sprites, game_map * pMap );
	~Guard();
	virtual void movement();	
	
private:
	void patrol();
	void chase( point waypoint );
	bool isMoveBlocked( float delta );
	line_of_sight * _los;
	Text * _text;
	game_map* _pMap;

	void checkCaptures();
	bool _chase;
	

};

#endif // _GUARD_H_

