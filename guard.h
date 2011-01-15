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

class Guard : public game_sprite
{
public:
	Guard( float start_x, float start_y );
	void RoamForever();
	
};

#endif // _GUARD_H_

