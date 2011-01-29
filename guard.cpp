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

Guard::Guard( float start_x, float start_y,  std::vector<game_sprite*> * sprites ) :
	_upCount(0),
	_downCount(MAX_DOWN),
	_rightCount(MAX_RIGHT),
	_leftCount(MAX_LEFT),
	_los(0),
	_text(0)
{
	// do some basic setup
	_players = sprites;
	_x = start_x;
	_y = start_y;
	width = GUARD_WIDTH;
	height = GUARD_HEIGHT;
	texture = LoadTexture( GUARD_IMAGE );
	includeAnimation(ANIM_NONE, texture, 0);
	useAnimation(ANIM_NONE);
	
	_los = new line_of_sight( FIELD_OF_VISION, DEPTH_OF_VISION, height, width, sprites );
	setDrawable( _los );

	_text = new Text();
	setDrawable( _text );	
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

	// This is a square roaming pattern	
	if ( _upCount < MAX_UP )
	{
		up();
		if ( _upCount >= MAX_UP )
		{
			_rightCount = 0;
			_angle = 90.0;
		}
	}
	else if ( _rightCount < MAX_RIGHT )
	{
		right();
		if ( _rightCount >= MAX_RIGHT )
		{
			_downCount = 0;
			_angle = 180.0;
		}
	}
	else if ( _downCount < MAX_DOWN )
	{
		down();
		if ( _downCount >= MAX_DOWN )
		{
			_leftCount = 0;
			_angle = -90.0;
		}
	}
	else if ( _leftCount < MAX_LEFT )
	{
		left();
		if ( _leftCount >= MAX_LEFT )
		{
			_upCount =  0;
			_angle = 0.0;
		}
	}
	
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
	
	vector<pair<float, float> > visibleSprites = _los->detect_visible_sprites();

	//_text->printf( "Sprites in line of sight: %d", visibleSprites.size() );
	_text->printf( "Guard X: %5.4f  Guard Y: %5.4f\nI see %d objects.", disp_x, disp_y, visibleSprites.size() );
	checkCaptures();
}

void Guard::up()
{
	//_y += DELTA;
	_upCount++;

}
void Guard::down()
{
	//_y -= DELTA;
	_downCount++;
}
void Guard::right()
{
	//_x += DELTA;
	_rightCount++;
}
void Guard::left()
{
	//_x -= DELTA;
	_leftCount++;
}

void Guard::checkCaptures(){
	
	std::vector<game_sprite *>::iterator itr = _players->begin();
	while( itr != _players->end() )
	{	
		float x1 = _x;
		float y1 = _y;
		float x2 = _x + width;
		float y2 = _y + height;
		float sprite_x1 = (*itr)->_x;
		float sprite_y1 = (*itr)->_y;
		float sprite_x2 = (*itr)->_x + (*itr)->width;
		float sprite_y2 = (*itr)->_y + (*itr)->height;
		
		if (boxCollision( _x, _y, _x + width, _y + height, (*itr)->_x, (*itr)->_y, (*itr)->_x + (*itr)->width, (*itr)->_y + (*itr)->height) || 
			boxCollision((*itr)->_x, (*itr)->_y, (*itr)->_x + (*itr)->width, (*itr)->_y + (*itr)->height, _x, _y, _x + width, _y + height )){
			if ( (*itr)->active ) {
				//pickupScore++;
				(*itr)->useAnimation(ANIM_EXPLODE);
			}
		}
		
		/*if (boxCollision(_x, _y, _x + width, _y + height, (*itr)->_x, (*itr)->_y, (*itr)->width + (*itr)->_x, (*itr)->height) + (*itr)->_y || 
			boxCollision((*itr)->_x, (*itr)->_y, (*itr)->_x + (*itr)->width, (*itr)->_y + (*itr)->height, _x, _y, _x + width, _y + height )){
			if ( (*itr)->active ) {
				//pickupScore++;
				(*itr)->useAnimation(ANIM_EXPLODE);
			}
		}*/
		++itr;
	}
}