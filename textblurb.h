/*
 *  textblurb.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/26/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#ifndef _TEXTBLURB_H_
#define _TEXTBLURB_H_

#include "spriteText.h"

class spriteText;

class textBlurb : public spriteText
{
public:
	textBlurb( float _rx, float _ry, const char * fmt, ... );
	~textBlurb();
	virtual void movement();
};

#endif // _TEXTBLURB_H_