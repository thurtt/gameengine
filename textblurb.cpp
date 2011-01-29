/*
 *  textblurb.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/26/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include <cstdio>
#include <cstdarg>

#include "textblurb.h"


textBlurb::textBlurb( float _rx, float _ry, const char * fmt, ... )
{
	xy(0,0);
	wh(6,13);
	
	expiration = 15;
	relative_x = _rx;
	relative_y = _ry;
	setAttribute(BLOCK_MOVEMENT, 0);
	setAttribute(BLOCK_VISIBILITY, 0);
	setAttribute(ALIVE, 1);
	setAttribute(EXPIRATION, 15);
	setAttribute(EXPIRATION_TICK, 0);
	alpha = 1.0f;
	
	includeAnimation(ANIM_NONE, LoadTexture("font_file"), 0);
	useAnimation(ANIM_NONE);
	
	va_list va_args;
	
	va_start( va_args, fmt );
	vprintf(fmt, va_args);
	//adjust for center 
	int adjust;
	adjust = (width * textLen)/2;
	relative_x -= adjust;
}

textBlurb::~textBlurb()
{
}

void textBlurb::movement()
{
	spriteText::movement();
}

void textBlurb::animate()
{
	relative_y += 0.8f;
	alpha -= 0.03f;		//too fun! :)
	spriteText::animate();
}
