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
	
	float bottom_y = eye_y - ( _fov / 2 );
	float top_y = eye_y + ( _fov / 2 );
	float left_x = eye_x;
	float right_x = eye_x + _dov;
	
	// make sure everything is gone
	_corners.clear();
	
	// bottom left
	_corners.push_back( line( rotate( left_x, bottom_y, eye_x, eye_y, angle ), rotate( left_x, top_y, eye_x, eye_y, angle ) ) );
	
	// top left
	_corners.push_back( line( rotate( left_x, top_y, eye_x, eye_y, angle ), rotate( right_x, top_y, eye_x, eye_y, angle ) ) );
	
	// top right
	_corners.push_back( line( rotate(  right_x, top_y, eye_x, eye_y, angle ), rotate(  right_x, bottom_y, eye_x, eye_y, angle ) ) );
	
	// bottom right
	_corners.push_back( line( rotate( right_x, bottom_y, eye_x, eye_y, angle ), rotate( left_x, bottom_y, eye_x, eye_y, angle ) ) );
	
	glMatrixMode( GL_MODELVIEW );	
	glPushMatrix();
	glLoadIdentity();
	
	glBegin( GL_LINES );
	glColor4f( 1.0f, 0.0f, 0.0f, 0.5f );

	
	polyIterator itr = _corners.begin();
	while( itr != _corners.end() )
	{
		glVertex2f( itr->getPoint1().x, itr->getPoint1().y );
		glVertex2f( itr->getPoint2().x, itr->getPoint2().y );

		++itr;
	}

	glEnd();
	glPopMatrix();

}

std::vector<point> line_of_sight::detect_visible_sprites()
{
	std::vector<game_sprite *>::iterator itr = _sprites->begin();
	std::vector<point> visible_sprites;

	while( itr != _sprites->end() )
	{
		if ( in_my_box( (*itr)->disp_x, (*itr)->disp_y, (*itr)->height, (*itr)->width ) && (*itr)->active )
		{
			visible_sprites.push_back( point( (*itr)->_x, (*itr)->_y ) );
		}
		++itr;
	}

	return visible_sprites;
}

bool line_of_sight::in_my_box( float x, float y, float h, float w )
{
	// Here is the code to use boxCollision, so we can make changes in only one place	
	if( _corners.size() == 0 ) return false;
	
	polygon poly2;
	poly2.push_back( line( x, y, x, y + h ) );
	poly2.push_back( line( x, y + h, x + w, y + h ) );
	poly2.push_back( line( x + w, y + h, x + w, y ) );
	poly2.push_back( line( x + w, y, x, y ) );
	
	// for our box
	point point1 = _corners[0].getPoint1();
	point point2 = _corners[1].getPoint2();
	return ( polygonCollision( _corners, poly2 ) );
	
}

point line_of_sight::rotate( float point_x, float point_y, float orig_x, float orig_y, float angle )
{
	// DANGER: Math zone
	// convert degrees to radians
	float rad_angle = ( -angle * M_PI ) / 180.0;

	// the trig identities used for rotation
	float x_prime = orig_x + ( ( ( point_x - orig_x ) * cos( rad_angle ) ) - ( ( point_y - orig_y ) * sin( rad_angle ) ) );
	float y_prime = orig_y + ( ( ( point_x - orig_x ) * sin( rad_angle ) ) + ( ( point_y - orig_y ) * cos( rad_angle ) ) );

	// End of DANGER
	return point( x_prime, y_prime );
}