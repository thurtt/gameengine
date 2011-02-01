/*
 *  buttonsprite.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/31/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "buttonsprite.h"
#include "button_defines.h"

button_sprite::button_sprite()
{
}

button_sprite::button_sprite(float x, float y, float h, float w, char * texture_file, int ret_val)
{
	xy(x,y);
	wh(w,h);
	
	setAttribute(BLOCK_MOVEMENT, 0);
	setAttribute(BLOCK_VISIBILITY, 0);
	setAttribute(ALIVE, 1);
	setAttribute(EXPIRATION, 0);
	setAttribute(EXPIRATION_TICK, 0);
	setAttribute(BUTTON_RETURN_VALUE, ret_val);
	active = true;
	
	includeAnimation(ANIM_NONE, LoadTexture(texture_file), 0);
	includeAnimation(ANIM_BUTTON_UP, LoadTexture(texture_file), 3);
	includeAnimation(ANIM_BUTTON_DOWN, LoadTexture(texture_file), 3);
	useAnimation(ANIM_BUTTON_UP);
	_angle = 0.0f;
	disp_x = 0.0;
	disp_y = 0.0;
	
}

button_sprite::~button_sprite()
{
}

int button_sprite::click(int state, int x, int y)
{
	//both mouse click AND release are sent. track that.
	
	switch (state) {
		case GLUT_DOWN:
			//DEPRESSED
			//frame = 1; //two frames of animation: up and down.
			
			useAnimation(ANIM_BUTTON_DOWN);
			return EVENT_ACCEPTED;
			break;
		case GLUT_UP:
			//up
			//frame = 0; // up.
			useAnimation(ANIM_BUTTON_UP);
			return getAttribute(BUTTON_RETURN_VALUE);
			break;

		default:
			break;
	}
	return NO_EVENT;
}

void button_sprite::clear()
{
	frame = 0;
}

/*void button_sprite::animate()
{
	//bail. animate based off of click state.
}
 */
