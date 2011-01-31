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

#define _USE_MATH_DEFINES
#include <math.h>

Guard::Guard( float start_x, float start_y,  std::vector<game_sprite*> * sprites ) :
	_los(0),
	_text(0),
	_target(0, 0)
{
	// do some basic setup
	_players = sprites;
	_x = start_x;
	_y = start_y;
	_target.x = start_x;
	_target.y = start_y;
	
	width = GUARD_WIDTH;
	height = GUARD_HEIGHT;
	texture = LoadTexture( GUARD_IMAGE );
	
	setAttribute(BLOCK_MOVEMENT, 0);
	setAttribute(BLOCK_VISIBILITY, 0);
	setAttribute(ALIVE, 1);
	
	includeAnimation(ANIM_NONE, texture, 0);
	useAnimation(ANIM_NONE);
	
	_los = new line_of_sight( FIELD_OF_VISION, DEPTH_OF_VISION, height, width, sprites );
	setDrawable( _los );

	_text = new Text();
	setDrawable( _text );
	
	// add a shitload of waypoints (para ahora, no es muy elegante...lo siento)
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
	
	vector<point> visibleSprites = _los->detect_visible_sprites();
	
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
		chase( visibleSprites[0] );
		_chase = true;
	}
	_text->printf( "Guard X: %5.4f  Guard Y: %5.4f\nI see %d objects.", disp_x, disp_y, visibleSprites.size() );
	checkCaptures();
}

void Guard::checkCaptures(){
	std::vector<game_sprite *>::iterator itr = _players->begin();
	while( itr != _players->end() )
	{	
		if (boxCollision( _x, _y, _x + width, _y + height, (*itr)->_x, (*itr)->_y, (*itr)->_x + (*itr)->width, (*itr)->_y + (*itr)->height) || 
			boxCollision((*itr)->_x, (*itr)->_y, (*itr)->_x + (*itr)->width, (*itr)->_y + (*itr)->height, _x, _y, _x + width, _y + height )){
			if ( (*itr)->active ) {
				(*itr)->useAnimation(ANIM_EXPLODE);
			}
		}
		++itr;
	}
}

void Guard::chase( point waypoint )
{
	_target = waypoint;
	move( CHASE_DELTA );
}

void Guard::patrol()
{
	if ( close_enough( _target, point( _x, _y ) ) )
	{
		_target = _wpmgr.getNextWaypoint();
	}
	else
	{
		move( PATROL_DELTA );
	}	
}

bool Guard::close_enough( const point & point1, const point & point2 )
{
	return( point2.x <= point1.x + 5 && point2.x >= point1.x - 5
		   && point2.y <= point1.y + 5 && point2.y >= point1.y - 5 );
}

point Guard::move( float delta )
{
	float rad_angle = atan2( ( _target.y - _y ), ( _target.x - _x ) );
	_angle = -toDegrees( rad_angle );
	_x += delta * cos( rad_angle );		
	_y += delta * sin( rad_angle );
}


