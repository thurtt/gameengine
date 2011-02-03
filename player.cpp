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
#include "textblurb.h"
#include "los.h"
#include "text.h"
#include "collision.h"

Player::Player( float _x_, float _y_, float _width_, float _height_, const char * _filename,  std::vector<game_sprite*> * sprites,  std::vector<game_sprite*> * pickups, game_map * pMap  ) :
_sprites(sprites),
_pickups(pickups),
_pMap(pMap)
{
	// do some basic setup
	xy(_x_, _y_);
	wh(_width_, _height_);
	texture_file = _filename;
	attr = new spriteAttribute();
	
	attr->setAttribute(PICKUP_SCORE, 0);
	attr->setAttribute(BLOCK_MOVEMENT, 0);
	attr->setAttribute(BLOCK_VISIBILITY, 0);
	attr->setAttribute(ALIVE, 1);
	
	texture = LoadTexture(texture_file);
	includeAnimation(ANIM_NONE, texture, 0);
	includeAnimation(ANIM_EXPLODE, "explosion.png", 25);
	includeAnimation(ANIM_WALK, "player_walking_64.png", 8);
	useAnimation(ANIM_NONE);
	
	
	//sprite_list.push_back(new spriteText(0, height, 13, 6, 300, "Player 1"));
	//sprite_list.push_back(new spriteText(0, 0, 13, 6, 0, "Player X: %5.4f  Player Y: %5.4f", _x_, _y_));
}

void Player::movement(){	
	//game_sprite::movement();
	
	float delta = 0.8;
	float temp_x = _x;
	float temp_y = _y; // <---- store temporary coords for collision testing.
	//texture = 1;
	if ((move_right > 0) || (move_left > 0) || (move_up > 0) || (move_down > 0)){
		if (texture != animations[ANIM_WALK].first) {
			useAnimation(ANIM_WALK);
		}
	}
	
	if (move_right > 0)	{ 
		temp_x = _x + delta; 
		_angle = 90;
	}
	if (move_left > 0)	{ 
		temp_x = _x - delta; 
		_angle = 270;
	}
	if (move_up > 0)	{ 
		temp_y = _y + delta;
		_angle = 0;
	}
	if (move_down > 0)	{ 
		temp_y = _y - delta;
		_angle = 180;
	}
	
	// get textures for new position:
	vector<tile*> pTiles;
	pTiles = _pMap->getTiles(temp_x, temp_y, height, width);
	int i, k;
	bool move_allowed = true;
	for (i = 0; i < pTiles.size(); i++){
		for (k = 0; k < pTiles[i]->sprites.size(); k++){
			if (pTiles[i]->sprites[k]->attr->getAttribute(BLOCK_MOVEMENT) > 0){
				if ( boxCollision(
								  pTiles[i]->sprites[k]->_x, pTiles[i]->sprites[k]->_y,
								  pTiles[i]->sprites[k]->_x + pTiles[i]->sprites[k]->width, 
								  pTiles[i]->sprites[k]->_y + pTiles[i]->sprites[k]->height, 
								  temp_x, temp_y, 
								  temp_x + width, temp_y + height)  ||
					boxCollision(
								 temp_x, temp_y, 
								 temp_x + width, temp_y + height,
								 pTiles[i]->sprites[k]->_x, pTiles[i]->sprites[k]->_y,
								 pTiles[i]->sprites[k]->_x + pTiles[i]->sprites[k]->width, 
								 pTiles[i]->sprites[k]->_y + pTiles[i]->sprites[k]->height) ) {
					//we can't do this
					move_allowed = false;
				}
			}
		}
	}
	if (move_allowed){
		_x = temp_x;
		_y = temp_y;
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
}

void Player::checkPickups(){
	
	int original_pickup = attr->getAttribute(PICKUP_SCORE);
	
	std::vector<game_sprite *>::iterator itr = _pickups->begin();
	while( itr != _pickups->end() )
	{
		if (boxCollision(_x, _y, _x + width, _y + height, (*itr)->_x, (*itr)->_y, (*itr)->_x + (*itr)->width, (*itr)->_y + (*itr)->height) || 
			boxCollision((*itr)->_x, (*itr)->_y, (*itr)->_x + (*itr)->width, (*itr)->_y + (*itr)->height, _x, _y, _x + width, _y + height )){
			if ( (*itr)->active && ((*itr)->attr->getAttribute(ALIVE) > 0) ) {
				attr->setAttribute(PICKUP_SCORE, attr->getAttribute(PICKUP_SCORE) + 1);
				(*itr)->useAnimation(ANIM_EXPLODE);
			}
		}
		++itr;
	}
	if (original_pickup < attr->getAttribute(PICKUP_SCORE)){
		sprite_list.push_back(new textBlurb(width / 2, height, "+ %d", attr->getAttribute(PICKUP_SCORE) - original_pickup));
	}	
}

