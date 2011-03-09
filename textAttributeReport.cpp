/*
 *  textAttributeReport.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/30/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "textAttributeReport.h"


textAttributeReport::textAttributeReport(  float _x, float _y, game_sprite * monitor_sprite, int monitor, const char * fmt ) :
_monitor_attribute(monitor),
_monitor_sprite(monitor_sprite),
_fmt(fmt)
{
	xy(_x,_y);
	wh(16,16);
	
	relative_x = 0;
	relative_y = 0;
	attr = new spriteAttribute();
	
	attr->setAttribute(BLOCK_MOVEMENT, 0);
	attr->setAttribute(BLOCK_VISIBILITY, 0);
	attr->setAttribute(ALIVE, 1);
	attr->setAttribute(EXPIRATION, 0);
	attr->setAttribute(EXPIRATION_TICK, 0);
	alpha = 1.0f;
	
	sp_height = 32;
	sp_width = 32;
	includeAnimation(ANIM_NONE, LoadTexture("alphatiles_32.png"), 94);
	useAnimation(ANIM_NONE);
	
	update();
}

textAttributeReport::~textAttributeReport()
{
}

void textAttributeReport::update()
{
	printf(_fmt, _monitor_sprite->attr->getAttribute(_monitor_attribute));
}

void textAttributeReport::movement()
{
	update();
	spriteText::movement();
}

void textAttributeReport::animate()
{
	spriteText::animate();
}
void textAttributeReport::draw(float offset_x, float offset_y)
{
	update();
	spriteText::draw(offset_x,offset_y);
}