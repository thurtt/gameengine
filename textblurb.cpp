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
	
	expiration = 5;
	relative_x = _rx;
	relative_y = _ry;
	_blockMovement = false;
	_blockVisibility = false;
	expiration_tick = 0;
	
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

textBlurb::~textBlurb(){
}

void textBlurb::movement(){
	spriteText::movement();
}
