/*
 *  los.cpp
 *  gltest
 *
 *  Created by tom on 1/15/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "los.h"
#include "collision.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>
#include <utility>
#include <map>
#define _USE_MATH_DEFINES
#include <math.h>


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
	
	float bottom_x = eye_x - ( _fov / 2 );
	float top_x = eye_x + ( _fov / 2 );
	float left_y = eye_y;
	float right_y = eye_y + _dov;
	
	// calculate the corners applying the angle of rotation
	// bottom left
	pair< float, float > tmp_xy;
	
	tmp_xy = rotate( bottom_x, left_y, eye_x, eye_y, angle );
	_corners[0][0] = tmp_xy.first;
	_corners[1][0] = tmp_xy.second;
	
	// top left
	tmp_xy = rotate( top_x, left_y, eye_x, eye_y, angle );
	_corners[0][1] = tmp_xy.first;
	_corners[1][1] = tmp_xy.second;
	
	// top right
	tmp_xy = rotate( top_x, right_y, eye_x, eye_y, angle );
	_corners[0][2] = tmp_xy.first;
	_corners[1][2] = tmp_xy.second;
	
	// bottom right
	tmp_xy = rotate( bottom_x, right_y, eye_x, eye_y, angle );
	_corners[0][3] = tmp_xy.first;
	_corners[1][3] = tmp_xy.second;
	
	glMatrixMode( GL_MODELVIEW );	
	glPushMatrix();
	glLoadIdentity();
	
	glBegin( GL_LINES );
	glColor4f( 1.0f, 0.0f, 0.0f, 0.5f );			// Full Brightness, 0.5f == 50% Alpha ( NEW )

	// create and connect the vertices
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
		if ( in_my_box( (*itr)->disp_x, (*itr)->disp_y, (*itr)->height, (*itr)->width ) )
		{
			std::pair<float, float> tmpPair;
			tmpPair.first = (*itr)->disp_x;
			tmpPair.second = (*itr)->disp_y;
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
	return (boxCollision(x, y, h, w, _corners[0][0], _corners[0][1], my_height, my_width ) ||
			boxCollision(_corners[0][0], _corners[0][1], my_height, my_width,x, y, h, w ));
	
}

pair< float, float > line_of_sight::rotate( float point_x, float point_y, float orig_x, float orig_y, float angle )
{
	// DANGER: Math zone
	// convert degrees to radians
	float rad_angle = ( -angle * M_PI ) / 180.0;

	// the trig identities used for rotation
	float x_prime = orig_x + ( ( ( point_x - orig_x ) * cos( rad_angle ) ) - ( ( point_y - orig_y ) * sin( rad_angle ) ) );
	float y_prime = orig_y + ( ( ( point_x - orig_x ) * sin( rad_angle ) ) + ( ( point_y - orig_y ) * cos( rad_angle ) ) );

	// End of DANGER
	pair< float, float > xy_prime( x_prime , y_prime );
	return xy_prime;
}