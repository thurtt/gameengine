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

#define VISION_DEBUG

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
	
	if ( _visibleSprites.size() > 0 )
	{
		glVertex2f( eye_x, eye_y );
		glVertex2f( _visibleSprites[0]->disp_x + (_visibleSprites[0]->width / 2), _visibleSprites[0]->disp_y + (_visibleSprites[0]->height / 2) );	
	}

	glEnd();
	glPopMatrix();
#endif

}

std::vector<game_sprite *> line_of_sight::detect_visible_sprites( float eye_x, float eye_y )
{
	
	std::vector<game_sprite *>::iterator itr = _sprites->begin();
	_visibleSprites.clear();

	if ( _corners.size() == 0 ) return _visibleSprites;
	
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
			line rayToSprite( eye_x, eye_y, (*itr)->disp_x, (*itr)->disp_y );
			
			// work through the list of blocking sprites, and check intersection
			vector<game_sprite *>::iterator blockItr = blockingSprites.begin();
			int intersectCount = 0;
			
			if( blockingSprites.size() > 0 )
			{
				while( blockItr != blockingSprites.end() )
				{
					// the sprite is some sort of rectangular square thingy
					polygon testBox;
					float s_x1 = (*blockItr)->disp_x;
					float s_y1 = (*blockItr)->disp_y;
					float s_x2 = (*blockItr)->disp_x + (*blockItr)->width;
					float s_y2 = (*blockItr)->disp_y + (*blockItr)->height;
					testBox.push_back( line( s_x1, s_y1, s_x1, s_y2 ) );
					testBox.push_back( line( s_x1, s_y2, s_x2, s_y2 ) );
					testBox.push_back( line( s_x2, s_y2, s_x2, s_y1 ) );
					testBox.push_back( line( s_x2, s_y1, s_x1, s_y1 ) );
					
					if ( !linePolyCollision( rayToSprite, testBox ) )
					{
						_visibleSprites.push_back( *itr );
					}
					
					++blockItr;
				}
			}
			else 
			{
				_visibleSprites.push_back( *itr );
			}

		}
		++itr;
	}

	return _visibleSprites;
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
	//return( sprite->getAttribute( BLOCK_VISIBILITY ) != 0 );
	return false;
}
