/*
 *  buttonsprite.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/31/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#ifndef BUTTONSPRITE_H
#define BUTTONSPRITE_H

#include "sprite.h"


class game_sprite;

class button_sprite : public game_sprite {
private:
	
public:
	button_sprite();
	button_sprite(float x, float y, float h, float w, const char * texture, int ret_val);
	~button_sprite();
	int click(int state, int x, int y);
	//void animate();
	void clear();
};

#endif //BUTTONSPRITE_H