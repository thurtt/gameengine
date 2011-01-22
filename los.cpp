/*
 *  los.cpp
 *  gltest
 *
 *  Created by tom on 1/15/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "los.h"
#include "sprite.h"
#include "collision.h"

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

line_of_sight::line_of_sight( float fov, float dov, float height, float width, std::vector<game_sprite*> * sprites ) :
_fov(fov),
_dov(dov),
_height(height),
_width(width),
_sprites(sprites)
{
}

void line_of_sight::draw( float x, float y, float angle )
{
	float eye_x = x + ( _width / 2 );
	float eye_y = y + ( _height / 2 );
	
	// build our list of corners
	// ugly looking, but fast
	// assuming angle of 0 degrees

	// bottom left
	_corners[0][0] = eye_x - ( _fov / 2 );
	_corners[1][0] = eye_y;
	
	// top left
	_corners[0][1] = eye_x + ( _fov / 2 );
	_corners[1][1] = eye_y;
	
	// top right
	_corners[0][2] = _corners[0][1];
	_corners[1][2] = eye_y + _dov;
	
	// bottom right
	_corners[0][3] = _corners[0][0];
	_corners[1][3] = eye_y + _dov;
	
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

	glVertex2f( _corners[0][0], _corners[1][0] );
	glVertex2f( _corners[0][1], _corners[1][1] );
	glVertex2f( _corners[0][1], _corners[1][1] );
	glVertex2f( _corners[0][2], _corners[1][2] );
	glVertex2f( _corners[0][2], _corners[1][2] );
	glVertex2f( _corners[0][3], _corners[1][3] );
	glVertex2f( _corners[0][3], _corners[1][3] );
	glVertex2f( _corners[0][0], _corners[1][0] );

	glEnd();
	glPopMatrix();
	
}

std::vector<std::pair< float, float> > line_of_sight::detect_visible_sprites()
{
	std::vector<game_sprite *>::iterator itr = _sprites->begin();
	std::vector<std::pair< float, float> > visible_sprites;

	while( itr != _sprites->end() )
	{
		if ( in_my_box( (*itr)->_x, (*itr)->_y, (*itr)->height, (*itr)->width ) )
		{
			std::pair<float, float> tmpPair;
			tmpPair.first = (*itr)->_x;
			tmpPair.second = (*itr)->_y;
			visible_sprites.push_back( tmpPair );
		}
		++itr;
	}

	return visible_sprites;
}

bool line_of_sight::in_my_box( float x, float y, float h, float w )
{
	// Here is the code to use boxCollision, so we can make changes in only one place
	float my_width = _corners[0][1] - _corners[0][0];
	float my_height = _corners[1][2] - _corners[1][0];
	return boxCollision(x, y, h, w, _corners[0][0], _corners[0][1], my_height, my_width );
	
	//original. This makes the assumption that the LOS rect is bigger than the target rect.
	/*
	if ( x + h > _corners[0][1] 
		|| x < _corners[0][0]
		|| y < _corners[1][0]
		|| y + w > _corners[1][2] )
	{
		return false;
	}

	return true;*/
}