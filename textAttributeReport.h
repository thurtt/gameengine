/*
 *  textAttributeReport.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/30/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */


#ifndef _textAttributeReport_H_
#define _textAttributeReport_H_

#include "spriteText.h"

class spriteText;

class textAttributeReport : public spriteText
{
public:
	textAttributeReport( float _x, float _y, game_sprite * monitor_sprite, int monitor, const char * fmt );
	~textAttributeReport();
	virtual void movement();
	virtual void animate();
	virtual void draw (float offset_x, float offset_y);
	void update();
	game_sprite * _monitor_sprite;
	int _monitor_attribute;
	const char * _fmt;
};

#endif // _textAttributeReport_H_