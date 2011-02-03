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
#include "rotation.h"

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

line_of_sight::line_of_sight( float fov, float dov, float height, float width, std::vector<game_sprite*> * sprites, game_map * pMap ) :
_fov(fov),
_dov(dov),
_height(height),
_width(width),
_sprites(sprites),
_pMap(pMap)
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

#ifdef VISION_DEBUG		
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
#endif

}

std::vector<point> line_of_sight::detect_visible_sprites( float my_x, float my_y )
{
	std::vector<game_sprite *>::iterator itr = _sprites->begin();
	std::vector<point> visible_sprites;

	if ( _corners.size() == 0 ) return visible_sprites;
	
	// get a list of tiles inside the vision box
	vector<tile *> tiles = _pMap->getTiles( _corners[0].getPoint1().x, _corners[0].getPoint2().y, _fov, _dov );
	vector<tile *>::iterator itrTiles = tiles.begin();

	// get a list of sprites that are blocking
	vector<game_sprite *> blockingSprites;
	vector<game_sprite *>::iterator itrTileSprites;

	while( itrTiles != tiles.end() )
	{
		itrTileSprites = (*itrTiles)->sprites.begin();
		while( itrTileSprites != (*itrTiles)->sprites.end() )
		{
			if( isBlocking( *itrTileSprites ) )
			{
				blockingSprites.push_back( *itrTileSprites );
			}
			++itrTileSprites;
		}
		++itrTiles;
	}
	
	while( itr != _sprites->end() )
	{
		if ( in_my_box( (*itr)->disp_x, (*itr)->disp_y, (*itr)->height, (*itr)->width ) && ((*itr)->attr->getAttribute(ALIVE) > 0) )
		{
			// check to see if there are any sprites blocking visibility
			line toSprite( my_x + (_dov / 2), my_y + (_fov / 2), (*itr)->_x + ((*itr)->width / 2), (*itr)->_y + ((*itr)->height / 2) );
			
			glMatrixMode( GL_MODELVIEW );	
			glPushMatrix();
			glLoadIdentity();
			
			glBegin( GL_LINES );
			glColor4f( 1.0f, 0.0f, 0.0f, 0.5f );
			glVertex2f( toSprite.getPoint1().x, toSprite.getPoint1().y );
			glVertex2f( toSprite.getPoint2().x, toSprite.getPoint2().y );
			glEnd();
			glPopMatrix();
			
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


bool line_of_sight::isBlocking( game_sprite * sprite )
{
	return( sprite->getAttribute( BLOCK_VISIBILITY ) != 0 );
}
