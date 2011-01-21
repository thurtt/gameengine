/*
 *  los.cpp
 *  gltest
 *
 *  Created by tom on 1/15/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "los.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>
#include <utility>
#include <map>

#ifdef WIN32
#include <freeglut.h>
#elif defined(__APPLE__) || defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GLUT/glut.h>
#endif

line_of_sight::line_of_sight( float fov, float dov, float height, float width ) :
_fov(fov),
_dov(dov),
_height(height),
_width(width)
{
}

void line_of_sight::draw( float x, float y, float angle )
{
	float eye_x = x + ( _width / 2 );
	float eye_y = y + ( _height / 2 );
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	glPushMatrix();
	glLoadIdentity();
	glTranslatef( eye_x, eye_y, 0.0 );	// <- the translation used was world x,y, so it was rotating around screen 0,0
	glRotatef( -angle, 0.0, 0.0, 1.0 ); // technically, you have to rotate this opposite to make it appear right.
	glTranslatef( -eye_x, -eye_y, -0.0 );
	
	glBegin( GL_LINES );
	glColor4f( 1.0f, 0.0f, 0.0f, 0.5f );			// Full Brightness, 0.5f == 50% Alpha ( NEW )
	
	// Two things happened here:
	//  angle 0deg is straight up for our dude, so we have to split the x coord instead of y (so it's not sideways)
	// we had to swap the FoV and DoV to get the long view you wanted.
	
	// left side of the box
	glVertex2f( eye_x - ( _fov / 2 ), eye_y );
	glVertex2f( eye_x + ( _fov / 2 ), eye_y );
	
	// top side
	glVertex2f( eye_x + ( _fov / 2 ), eye_y );
	glVertex2f( eye_x + ( _fov / 2 ), eye_y + _dov );
	
	// bottom side 
	glVertex2f( eye_x - ( _fov / 2 ), eye_y );
	glVertex2f( eye_x - ( _fov / 2 ), eye_y + _dov );
	
	// right side
	glVertex2f( eye_x - ( _fov / 2 ), eye_y + _dov );
	glVertex2f( eye_x + ( _fov / 2 ), eye_y + _dov );
	
	glEnd();
	glPopMatrix();
	
}