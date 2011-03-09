/*
 *  playerselectsprite.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 2/27/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "playerselectsprite.h"
#include "button_defines.h"

player_select_sprite::player_select_sprite()
{
}

player_select_sprite::player_select_sprite(float x, float y, float h, float w,  const char * texture_file, const char * name, int ret_val)
{
	xy(x,y);
	wh(w,h);
	
	attr->setAttribute(BLOCK_MOVEMENT, 0);
	attr->setAttribute(BLOCK_VISIBILITY, 0);
	attr->setAttribute(ALIVE, 1);
	attr->setAttribute(EXPIRATION, 0);
	attr->setAttribute(EXPIRATION_TICK, 0);
	attr->setAttribute(BUTTON_RETURN_VALUE, ret_val);
	active = true;
	
	includeAnimation(ANIM_NONE, LoadTexture(texture_file), 0);
	useAnimation(ANIM_NONE);
	_angle = 0.0f;
	disp_x = 0.0;
	disp_y = 0.0;
	
	sprite_list.push_back(new spriteText(0, height, 32, 32, 0, name));
}

player_select_sprite::~player_select_sprite()
{
}

int player_select_sprite::click(int state, int x, int y)
{
	//both mouse click AND release are sent. track that.
	
	
	switch (state) {
		case GLUT_DOWN:
			//DEPRESSED
			
			//useAnimation(ANIM_BUTTON_DOWN);
			return EVENT_ACCEPTED;
			break;
		case GLUT_UP:
			//up
			//useAnimation(ANIM_BUTTON_UP);
			return attr->getAttribute(BUTTON_RETURN_VALUE);
			break;
			
		default:
			break;
	}
	return NO_EVENT;
}

void player_select_sprite::clear()
{
	frame = 0;
}

void player_select_sprite::movement()
{
		std::vector<game_sprite *>::iterator itr = sprite_list.begin();
		while( itr != sprite_list.end() )
		{
			if ( (*itr)->active == true ){
				(*itr)->xy(_x , _y );
				(*itr)->movement( );
				++itr;
			}
			else{
				sprite_list.erase(itr);
			}
		}
}
