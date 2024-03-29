/*
 *  guard.cpp
 *  gltest
 *
 *  Created by tom on 1/15/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "guard.h"
#include "los.h"
#include "text.h"
#include "collision.h"
#include "rotation.h"
#include "tiles.h"

#define _USE_MATH_DEFINES
#include <math.h>

Guard::Guard( float start_x, float start_y,  std::vector<game_sprite*> * sprites, game_map * pMap ) :
	_los(0),
	_text(0),
	_pMap(pMap)
{
	// do some basic setup
	_players = sprites;
	_x = start_x;
	_y = start_y;
	_target.x = start_x;
	_target.y = start_y;
	
	attr = new spriteAttribute();
	
	width = GUARD_WIDTH;
	height = GUARD_HEIGHT;
	texture = LoadTexture( GUARD_IMAGE );
	
	attr->setAttribute(BLOCK_MOVEMENT, 0);
	attr->setAttribute(BLOCK_VISIBILITY, 0);
	attr->setAttribute(ALIVE, 1);
	
	includeAnimation(ANIM_NONE, texture, 0);
	useAnimation(ANIM_NONE);
	
	_los = new line_of_sight( FIELD_OF_VISION, DEPTH_OF_VISION, height, width, sprites, _pMap );
	setDrawable( _los );

	_text = new Text();
	setDrawable( _text );
	
	// add a shitload of waypoints (para ahora, no es muy elegante...lo siento)
	//_wpmgr.addWaypoint( point(473, 1300) );
	_wpmgr.addWaypoint( point(202, 800) );
	_wpmgr.addWaypoint( point(300, 800) );
	_wpmgr.addWaypoint( point(408, 650) );
	_wpmgr.addWaypoint( point(408, 900) );
	_wpmgr.addWaypoint( point(320, 900) );
	_wpmgr.addWaypoint( point(800, 800) );
	_wpmgr.addWaypoint( point(800, 1200) );
	_wpmgr.addWaypoint( point(700, 1200) );
	_wpmgr.addWaypoint( point(600, 1000) );
	_wpmgr.addWaypoint( point(202, 1000) );
	_wpmgr.addWaypoint( point(350, 1200) );
	_wpmgr.addWaypoint( point(550, 1200) );
}

Guard::~Guard()
{
	// this is a wee bit dangerous
	delete _los;
	_los = 0;

	delete _text;
	_text = 0;
}
void Guard::movement()
{	
	if (onscreen(disp_x, disp_y, height, width)){
		std::vector<game_sprite *>::iterator itr = sprite_list.begin();
		while( itr != sprite_list.end() )
		{
			if ( (*itr)->active == true ){
				(*itr)->xy(_x , _y );	//offer base xy?
				(*itr)->movement( );	// override this to apply relative xy
				++itr;
			}
			else{
				sprite_list.erase(itr);
			}
		}
	} 
	
	vector<game_sprite *> visibleSprites = _los->detect_visible_sprites( disp_x + (width / 2), disp_y + ( height /2 ), _x, _y );
	
	if( visibleSprites.size() == 0 )
	{
		if( _chase )
		{
			_chase = false;
			_wpmgr.reset();
			_target = _wpmgr.getNextWaypoint();
		}			
		patrol();
	}
	else 
	{
		chase( point( visibleSprites[0]->_x, visibleSprites[0]->_y ) );
		_chase = true;
	}
	
#ifdef VISION_DEBUG
	_text->printf( "Guard X: %5.4f  Guard Y: %5.4f\nI see %d objects.", disp_x, disp_y, visibleSprites.size() );
#endif
	
	checkCaptures();
}

void Guard::checkCaptures(){
	std::vector<game_sprite *>::iterator itr = _players->begin();
	while( itr != _players->end() )
	{	
		if (boxCollision( _x, _y, _x + width, _y + height, (*itr)->_x, (*itr)->_y, (*itr)->_x + (*itr)->width, (*itr)->_y + (*itr)->height) || 
			boxCollision((*itr)->_x, (*itr)->_y, (*itr)->_x + (*itr)->width, (*itr)->_y + (*itr)->height, _x, _y, _x + width, _y + height )){
			if ( (*itr)->active ) {
				(*itr)->captured();
				//(*itr)->useAnimation(ANIM_EXPLODE);
			}
		}
		++itr;
	}
}

void Guard::chase( point waypoint )
{
	_target = waypoint;
	if ( isMoveBlocked( CHASE_DELTA ) == false ) 
	{
		move( CHASE_DELTA );
	}
}

void Guard::patrol()
{
	if ( close_enough( _target, point( _x, _y ) ) )
	{
		_target = _wpmgr.getNextWaypoint();
	}
	else if ( isMoveBlocked( PATROL_DELTA ) == false )
	{
		move( PATROL_DELTA );
	}	
}

bool Guard::isMoveBlocked( float delta )
{
	// get textures for new position:
	point newPoint = get_next_step( delta );
	vector<tile*> pTiles = _pMap->getTiles( newPoint.x, newPoint.y, newPoint.x + height, newPoint.y + width);
	bool move_blocked = false;
	
	for (int i = 0; i < pTiles.size(); i++)
	{
		for (int k = 0; k < pTiles[i]->sprites.size(); k++)
		{
			if (pTiles[i]->sprites[k]->attr->getAttribute(BLOCK_MOVEMENT) > 0)
			{
				//we can't do this
				move_blocked = true;
			}
		}
	}
	return move_blocked;
}




