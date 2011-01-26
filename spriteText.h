/*
 *  spriteText.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/26/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */


#ifndef _SPRITETEXT_H_
#define _SPRITETEXT_H_

#include "sprite.h"

const unsigned long MAX_SPRITE_CHARS = 2048;

class Text;
class line_of_sight;
class game_sprite;

class spriteText : public game_sprite
{
public:
	spriteText(float _rx, float _ry, float _h_, float _w_,int exp, const char * fmt, ...   );
	~spriteText();
	virtual void movement();
	virtual void animate();
	void draw (float offset_x, float offset_y);
	float relative_x;
	float relative_y;
	int expiration;
	int expiration_tick; //counter for expiration.
	
private:	
	char * _msg;
	void write_string( float x, float y );
};

#endif // _SPRITETEXT_H_