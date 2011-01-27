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
	
	// make sure everything is gone
	_corners.clear();
	
	// bottom left
	_corners.push_back( rotate( bottom_x, left_y, eye_x, eye_y, angle ) );
	
	// top left
	_corners.push_back( rotate( top_x, left_y, eye_x, eye_y, angle ) );
	
	// top right
	_corners.push_back( rotate( top_x, right_y, eye_x, eye_y, angle ) );
	
	// bottom right
	_corners.push_back( rotate( bottom_x, right_y, eye_x, eye_y, angle ) );
	
	glMatrixMode( GL_MODELVIEW );	
	glPushMatrix();
	glLoadIdentity();
	
	glBegin( GL_LINES );
	glColor4f( 1.0f, 0.0f, 0.0f, 0.5f );

	std::vector< std::pair<float, float> >::iterator itr = _corners.begin();
	bool skipflag = true;
	while( itr != _corners.end() )
	{
		glVertex2f( (*itr).first, (*itr).second );
		
		if( itr == _corners.begin() )
		{
			++itr;
		}
		else if( skipflag )
		{
			skipflag = false;
		}
		else 
		{
			++itr;
			skipflag = true;
		}
	}
	
	// finish things up
	itr = _corners.begin();
	glVertex2f( (*itr).first, (*itr).second );

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
	/*float my_width = _corners[0][1] - _corners[0][0];
	float my_height = _corners[1][2] - _corners[1][0];
	return (boxCollision(x, y, h, w, _corners[0][0], _corners[1][0], my_height, my_width ) ||
			boxCollision(_corners[0][0], _corners[1][0], my_height, my_width,x, y, h, w ));*/
	
	std::vector< std::pair<float, float> > poly2;
	
	poly2.push_back( std::pair<float, float>( x, y ) );
	poly2.push_back( std::pair<float, float>( x, y + h ) );
	poly2.push_back( std::pair<float, float>( x + w, y + h ) );
	poly2.push_back( std::pair<float, float>( x + w, y ) );
	
	return polygonCollision( _corners, poly2 );
	
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