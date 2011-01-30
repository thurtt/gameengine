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
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>

Guard::Guard( float start_x, float start_y,  std::vector<game_sprite*> * sprites ) :
	_upCount(0),
	_downCount(MAX_DOWN),
	_rightCount(MAX_RIGHT),
	_leftCount(MAX_LEFT),
	_los(0),
	_text(0),
	_waypoint_index(0)
{
	// do some basic setup
	_players = sprites;
	_x = start_x;
	_y = start_y;
	_target_x = start_x;
	_target_y = start_y;
	
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
	
	// this is a terrible rng
	srand ( time(NULL) );
	
	// add a shitload of waypoints (para ahora, no es muy elegante...lo siento)
	_waypoints.push_back( point(202, 800) );
	_waypoints.push_back( point(300, 800) );
	_waypoints.push_back( point(408, 650) );
	_waypoints.push_back( point(408, 900) );
	_waypoints.push_back( point(320, 900) );
	_waypoints.push_back( point(800, 800) );
	_waypoints.push_back( point(800, 1200) );
	_waypoints.push_back( point(700, 1200) );
	_waypoints.push_back( point(600, 1000) );
	_waypoints.push_back( point(202, 1000) );
	_waypoints.push_back( point(350, 1200) );
	_waypoints.push_back( point(550, 1200) );
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
			_target_x = _waypoints[0].x;
			_target_y = _waypoints[0].y;
		}
			
		patrol();
	}
	else 
	{
		chase( visibleSprites[0] );
		_chase = true;
	}
	_text->printf( "Guard X: %5.4f  Guard Y: %5.4f\nI see %d objects.", disp_x, disp_y, visibleSprites.size() );
	if ( checkCaptures() )
	{
		_chase = false;
		_waypoint_index = 0;
	}
}

bool Guard::checkCaptures(){
	
	bool caught_the_bastard = false;
	std::vector<game_sprite *>::iterator itr = _players->begin();
	while( itr != _players->end() )
	{	
		if (boxCollision( _x, _y, _x + width, _y + height, (*itr)->_x, (*itr)->_y, (*itr)->_x + (*itr)->width, (*itr)->_y + (*itr)->height) || 
			boxCollision((*itr)->_x, (*itr)->_y, (*itr)->_x + (*itr)->width, (*itr)->_y + (*itr)->height, _x, _y, _x + width, _y + height )){
			if ( (*itr)->active ) {
				caught_the_bastard = true;
				(*itr)->useAnimation(ANIM_EXPLODE);
			}
		}
		++itr;
	}
	return caught_the_bastard;
}

void Guard::chase( point waypoint )
{
	_target_x = waypoint.x;
	_target_y = waypoint.y;
	
	float rad_angle = atan2( ( _target_y - _y ), ( _target_x - _x ) );
	_x += DELTA * 1.1 * cos( rad_angle );		
	_y += DELTA * 1.1 * sin( rad_angle );
}

void Guard::patrol()
{
	if( _x <= _target_x + 5
	    && _x >= _target_x - 5
	    && _y <= _target_y + 5
	    && _y >= _target_y - 5 )
	{			
		if( _waypoint_index == 11 )
		{
			_waypoint_index = 0;
		}
		else 
		{
			_waypoint_index++;
		}

		_target_x = _waypoints[_waypoint_index].x;
		_target_y = _waypoints[_waypoint_index].y;
		
		float rad_angle = atan2( ( _target_y - _y ), ( _target_x - _x ) );
		
		_angle = -( rad_angle * 180 ) / M_PI;
	}
	else 
	{
		float rad_angle = ( -_angle * M_PI ) / 180.0;
		_x += DELTA * .7 * cos( rad_angle );		
		_y += DELTA * .7 * sin( rad_angle );
	}	
}