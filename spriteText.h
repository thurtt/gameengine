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

class game_sprite;

class spriteText : public game_sprite
{
public:
	spriteText(float _rx, float _ry, float _h_, float _w_,int exp, const char * fmt, ...   );
	~spriteText();
	spriteText();
	void printf( const char * fmt, ... );
	void vprintf( const char * fmt, va_list va_args );
	virtual void movement();
	virtual void animate();
	virtual void draw (float offset_x, float offset_y);
	int getTextLen();
	float relative_x;
	float relative_y;
	float alpha;
	int textLen;
	char * _msg;
	int sp_height;
	int sp_width;
private:	
	void write_string( float x, float y );
};

#endif // _SPRITETEXT_H_