/*
 *  spriteText.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/26/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include <cstdio>
#include <cstdarg>

#include "spriteText.h"
#include "collision.h"

spriteText::spriteText( float _rx, float _ry, float _h_, float _w_, int exp, const char * fmt, ... )
{
	// do some basic setup
	xy(0, 0);
	wh(_w_, _h_);//square?
	GLuint texture;
	expiration = exp;
	relative_x = _rx;
	relative_y = _ry;
	_blockMovement = false;
	_blockVisibility = false;
	expiration_tick = 0;
	alpha = 1.0f;
	
	//get the right texture for the job.
	//maybe use mipmaps instead?
	if (height >= 64){
		texture = LoadTexture("font_file");
	}else if (height >= 32) {
		texture = LoadTexture("font_file");
	}else {
		texture = LoadTexture("font_file");
	}
	
	
	includeAnimation(ANIM_NONE, texture, 0);
	useAnimation(ANIM_NONE);	
	
	/* text processing stolen from Thomas. */
	
	_msg = new char[MAX_SPRITE_CHARS];
	va_list va_args;
	
	va_start( va_args, fmt );
	
	vsnprintf( _msg, MAX_SPRITE_CHARS, fmt, va_args );
	_msg[MAX_SPRITE_CHARS-1] = '\0';
}

spriteText::spriteText()
{
	//delete [] _msg;
}

spriteText::~spriteText()
{
	delete [] _msg;
}

int spriteText::getTextLen(){
	int i;
	
	for( i = 0; i < MAX_SPRITE_CHARS; i++ )
	{
		if ( _msg[i] == '\0' )
		{
			break;
		}
	}
	return i;
}

void spriteText::vprintf(const char * fmt, va_list va_args){
	
	_msg = new char[MAX_SPRITE_CHARS];
	
	vsnprintf( _msg, MAX_SPRITE_CHARS, fmt, va_args );
	_msg[MAX_SPRITE_CHARS-1] = '\0';
	textLen = getTextLen();
	
}

void spriteText::printf( const char * fmt, ... )
{
	va_list va_args;
	
	va_start( va_args, fmt );
	vprintf(fmt, va_args);
}

void spriteText::movement(){
	_x += relative_x;
	_y += relative_y;
}

void spriteText::animate(){
	frame++;
	
	switch (texture) {
		case ANIM_NONE:
			//refuse animation here.
			frame = 0;
			break;
		case ANIM_IDLE:
			break;
		case ANIM_WALK:
			break;
		case ANIM_RUN:
			break;
		case ANIM_ACTIVATE:
			break;
		case ANIM_HIDE:
			break;
		case ANIM_EXPLODE:
			if (frame >= animations[texture].second ) {
				useAnimation(ANIM_NONE);
				active = false;
			}
			break;
		case ANIM_AMBIENT:
			break;
		default:
			break;
	}
	if(expiration > 0){
		//we can expire.
		expiration_tick++;
		if (expiration_tick > expiration) {
			active = false; //deactivate. killed on next automation hit.
		}
	}
	if (frame >= animations[texture].second ) frame = 0;

}

void spriteText::draw(float offset_x, float offset_y){
	float x = _x + offset_x;
	float y = _y + offset_y;
	float orig_x = x;
	
	disp_x = _x + offset_x + 0.0f;
	disp_y = _y + offset_y + 0.0f;
	
	
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glColor4f(1.0f,1.0f,1.0f,alpha);			// Full Brightness, 0.5f == 50% Alpha ( NEW )
	
	for( int i = 0; i < MAX_SPRITE_CHARS; i++ )
	{
		if ( _msg[i] == '\0' )
		{
			break;
		}
		if ( _msg[i] == '\n' )
		{
			y -= height; // this is now char height.
			x = orig_x;
			continue;
		}
		
		glRasterPos2f( x, y );
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, _msg[i] );
		x += width; // this is now char width.
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}
