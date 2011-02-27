/*
 *  playerselectsprite.h
 *  gltest
 *
 *  Created by Stuart Templeton on 2/27/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#ifndef PLAYERSELECTSPRITE_H
#define PLAYERSELECTSPRITE_H

#include "sprite.h"


class game_sprite;

class player_select_sprite : public game_sprite {
private:
	
public:
	player_select_sprite();
	player_select_sprite(float x, float y, float h, float w, const char * texture, int ret_val);
	~player_select_sprite();
	int click(int state, int x, int y);
	//void animate();
	void clear();
};

#endif //PLAYERSELECTSPRITE_H