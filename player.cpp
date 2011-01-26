/*
 *  player.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/23/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "player.h"
#include "spriteText.h"
#include "los.h"
#include "text.h"
#include "collision.h"

Player::Player( float _x_, float _y_, float _width_, float _height_, const char * _filename,  std::vector<game_sprite*> * sprites,  std::vector<game_sprite*> * pickups  ) :
_los(0),
_text(0),
_sprites(sprites),
_pickups(pickups)
{
	// do some basic setup
	pickupScore = 0;
	xy(_x_, _y_);
	wh(_width_, _height_);
	texture_file = _filename;
	_blockMovement = false;
	_blockVisibility = false;
	
	texture = LoadTexture(texture_file);
	includeAnimation(ANIM_NONE, texture, 0);
	includeAnimation(ANIM_EXPLODE, "explosion.png", 25);
	includeAnimation(ANIM_WALK, "player_walking_64.png", 8);
	useAnimation(ANIM_NONE);
	
	_los = new line_of_sight( 180.0, 250.0, 64, 64, sprites );
	setDrawable( _los );
	
	//_text = new Text();
	//setDrawable( _text );	
	
	//sprite_list.push_back(new spriteText(0, height, 13, 6, 300, "Player 1"));
	sprite_list.push_back(new spriteText(0, 0, 13, 6, 0, "Player X: %5.4f  Player Y: %5.4f", _x_, _y_));
}

Player::~Player()
{
	// this is a wee bit dangerous
	delete _los;
	_los = 0;
	
	delete _text;
	_text = 0;
}
void Player::movement(){	
	float delta = 0.8;
	//texture = 1;
	if ((move_right > 0) || (move_left > 0) || (move_up > 0) || (move_down > 0)){
		if (texture != animations[ANIM_WALK].first) {
			useAnimation(ANIM_WALK);
		}
	}
	
	if (move_right > 0)	{ 
		_x += delta; 
		_angle = 90;
	}
	if (move_left > 0)	{ 
		_x -= delta;
		_angle = 270;
	}
	if (move_up > 0)	{ 
		_y += delta;
		_angle = 0;
	}
	if (move_down > 0)	{ 
		_y -= delta; 
		_angle = 180;
	}
	
	if (onscreen(disp_x, disp_y, height, width)){
		std::vector<game_sprite *>::iterator itr = sprite_list.begin();
		while( itr != sprite_list.end() )
		{
			if ( (*itr)->active == true ){
				(*itr)->xy(_x , _y );
				(*itr)->movement( );
			++itr;
			}
			else{
				sprite_list.erase(itr);
			}
		}
	}
	
	checkPickups(); // check to see if we've snagged something.
	//_text->printf( "Player X: %5.4f  Player Y: %5.4f", disp_x, disp_y );
}

void Player::checkPickups(){
	
	int original_pickup = pickupScore;
	
	std::vector<game_sprite *>::iterator itr = _pickups->begin();
	while( itr != _pickups->end() )
	{
		if (boxCollision(_x, _y, height, width, (*itr)->_x, (*itr)->_y, (*itr)->height, (*itr)->width) || 
			boxCollision((*itr)->_x, (*itr)->_y, (*itr)->height, (*itr)->width, _x, _y, height, width )){
			if ( (*itr)->active ) {
				pickupScore++;
				(*itr)->useAnimation(ANIM_EXPLODE);
			}
		}
		++itr;
	}
	if (original_pickup < pickupScore){
		sprite_list.push_back(new spriteText(0, height, 13, 6, 5, "+ %d", pickupScore - original_pickup));
	}	
}

