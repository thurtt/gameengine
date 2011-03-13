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
#include <OpenGL/gl.h>

spriteText::spriteText( float _rx, float _ry, float _h_, float _w_, int exp, const char * fmt, ... )
{
	// do some basic setup
	xy(0, 0);
	wh(_w_, _h_);//square?
	GLuint texture;
	relative_x = _rx;
	relative_y = _ry;
	attr = new spriteAttribute();
	
	attr->setAttribute(BLOCK_MOVEMENT, 0);
	attr->setAttribute(BLOCK_VISIBILITY, 0);
	attr->setAttribute(ALIVE, 1);
	attr->setAttribute(EXPIRATION, exp);
	attr->setAttribute(EXPIRATION_TICK, 0);
	alpha = 1.0f;
	
	//get the right texture for the job.
	//maybe use mipmaps instead?
	
	if (height >= 64){
		sp_height = 64;
		sp_width = 64;
		includeAnimation(ANIM_NONE, "alphatiles.png", 94);
	}else if (height >= 32) {
		sp_height = 32;
		sp_width = 32;
		includeAnimation(ANIM_NONE, "alphatiles_32.png",94);
	}else if (height >= 16) {
		sp_height = 16;
		sp_width = 16;
		includeAnimation(ANIM_NONE, "alphatiles_16.png",94);
	}else {
		sp_height = 32;
		sp_width = 32;
		includeAnimation(ANIM_NONE, "alphatiles_32.png", 94);
	}
	
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
	_msg = new char[MAX_SPRITE_CHARS];
}

spriteText::~spriteText()
{
	delete [] _msg;
}

int spriteText::getTextLen(){
	// strlen is implemented in assembly
	// and is extremely fast.
	return strlen( _msg );
}

void spriteText::vprintf(const char * fmt, va_list va_args){
	
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
	if(attr->getAttribute(EXPIRATION) > 0){
		//we can expire.
		attr->setAttribute(EXPIRATION_TICK , attr->getAttribute(EXPIRATION_TICK) + 1);
		if (attr->getAttribute(EXPIRATION_TICK) > attr->getAttribute(EXPIRATION)) {
			active = false; //deactivate. killed on next automation hit.
		}
	}
	if (frame >= animations[texture].second ) frame = 0;

}

void spriteText::draw(float offset_x, float offset_y){
	if (!active)
		return;
	
	float x = _x + offset_x;
	float y = _y + offset_y;
	float orig_x = x;
	int texture_offset;
	int texture_x_offset;
	int texture_y_offset;
	int frames_width, frames_height;
	//GLint texture_width, texture_height;
	
	disp_x = _x + offset_x + 0.0f;
	disp_y = _y + offset_y + 0.0f;
	
	glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	
	glDisable(GL_DEPTH_TEST);
	glBindTexture( GL_TEXTURE_2D, animations[texture].first );
	
	//glGetTexLevelParameteriv(GL_TEXTURE_2D, 2, GL_TEXTURE_WIDTH, &texture_width);
	//glGetTexLevelParameteriv(GL_TEXTURE_2D, 2, GL_TEXTURE_HEIGHT, &texture_height);
	frames_width = 10; //(texture_width / sp_width);
	frames_height = 10; //(texture_height / sp_height);
	
	
	
	
	
	float translated_x = 0.0f;
	float translated_x2 = 1.0f;
	float translated_y = 0.0f;
	float translated_y2 = 1.0f;
	
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
		
		texture_offset = static_cast<int>(_msg[i]) - 32;
		texture_x_offset = texture_offset % frames_width;
		texture_y_offset = texture_offset / frames_width;// not a mistake, using frames_width
		
		translated_x = texture_x_offset * 0.1;
		translated_x2 = (texture_x_offset + 1) * 0.1;
		
		translated_y = 1 - texture_y_offset * 0.1;
		translated_y2 = 1 - (texture_y_offset + 1) * 0.1;
		
		glMatrixMode(GL_MODELVIEW);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		
		
		glPushMatrix();
		
		glBegin(GL_QUADS);
		glColor4f(1.0f,1.0f,1.0f,alpha);			// Full Brightness, 0.5f == 50% Alpha ( NEW )
		glTexCoord2d(translated_x,  translated_y2);	glVertex2f( x +  0.0f , y + 0.0f);
		glTexCoord2d(translated_x2, translated_y2);	glVertex2f( x + width , y + 0.0f );
		glTexCoord2d(translated_x2, translated_y);	glVertex2f( x + width , y + height);
		glTexCoord2d(translated_x,  translated_y);	glVertex2f( x +  0.0f , y + height);
		
		glEnd();
		
		glPopMatrix();
		x += width ; // this is now char width.
	}
	
	
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	
	
	
	
	
	
	/*
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
	 */
}
