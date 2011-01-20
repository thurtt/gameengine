/*
 *  drawable.h
 *  gltest
 *
 *  Created by tom on 1/18/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_
// This is a basic abstractish base class for any object that can be chained to a draw
// fuck yeah...

// Not much here at the moment; 
// maybe this was a dumb idea.
class drawable
{
public:
	virtual void draw( float x, float y, float angle ) = 0;
};
#endif // _DRAWABLE_H_