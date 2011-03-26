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

const float ROTATION_OFFSET = -90;

Player::Player( player_data * pdata, std::vector<game_sprite*> * sprites, std::vector<game_sprite*> * pickups, game_map * pMap  ) :
_sprites(sprites),
_pickups(pickups),
_pMap(pMap)
{	
	// do some basic setup
	xy( pdata->spawn.x, pdata->spawn.y );
	wh( pdata->width, pdata->height );
	texture_file = pdata->texture;
	attr = new spriteAttribute();
	
	attr->setAttribute(PICKUP_SCORE, 0);
	attr->setAttribute(BLOCK_MOVEMENT, 0);
	attr->setAttribute(BLOCK_VISIBILITY, 0);
	attr->setAttribute(ALIVE, 1);
	attr->setAttribute(PLAYER_LIVES, 3);
	
	texture = LoadTexture(texture_file);
	includeAnimation(ANIM_NONE, texture, 0);
	includeAnimation(ANIM_EXPLODE, "explosion.png", 25);
	includeAnimation(ANIM_WALK, "player_walking_64.png", 8);
	useAnimation(ANIM_NONE);
	_target = point( _x, _y );
	
	sprite_list.push_back(new spriteText(0, height, 12, 12, 0, pdata->name));
}

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
	attr->setAttribute(PLAYER_LIVES, 3);
	
	texture = LoadTexture(texture_file);
	includeAnimation(ANIM_NONE, texture, 0);
	includeAnimation(ANIM_EXPLODE, "explosion.png", 25);
	includeAnimation(ANIM_WALK, "player_walking_64.png", 8);
	useAnimation(ANIM_NONE);
	_target = point( _x, _y );
	
	sprite_list.push_back(new spriteText(0, height,12,12, 0, "Player 1"));
	//sprite_list.push_back(new spriteText(0, 0, 13, 6, 0, "Player X: %5.4f  Player Y: %5.4f", _x_, _y_));
}

void Player::movement(){	
	//game_sprite::movement();
	
	float delta = 0.8;
	texture = 1;
	
	if ( _wpmgr.getWaypointCount() )
	{
		_target = _wpmgr.popNextWaypoint();
	}
	
	// get textures for new position:
	vector<tile*> pTiles;
	pTiles = _pMap->getTiles( _x, _y, _x + height, _y + width);
	int i, k;
	bool move_allowed = true;
	point nextStep = get_next_step( delta );
	for (i = 0; i < pTiles.size(); i++){
		for (k = 0; k < pTiles[i]->sprites.size(); k++){
			if (pTiles[i]->sprites[k]->attr->getAttribute(BLOCK_MOVEMENT) > 0){
				if ( boxCollision(
								  pTiles[i]->sprites[k]->_x, pTiles[i]->sprites[k]->_y,
								  pTiles[i]->sprites[k]->_x + pTiles[i]->sprites[k]->width, 
								  pTiles[i]->sprites[k]->_y + pTiles[i]->sprites[k]->height, 
								  nextStep.x, nextStep.y, 
								  nextStep.x + width, nextStep.y + height)  ||
					boxCollision(
								 nextStep.x, nextStep.y, 
								 nextStep.x + width, nextStep.y + height,
								 pTiles[i]->sprites[k]->_x, pTiles[i]->sprites[k]->_y,
								 pTiles[i]->sprites[k]->_x + pTiles[i]->sprites[k]->width, 
								 pTiles[i]->sprites[k]->_y + pTiles[i]->sprites[k]->height) ) {
					//we can't do this
					move_allowed = false;
				}
			}
		}
	}
	if (move_allowed && !close_enough( point( _x, _y ), _target ) ){
		move( delta );
		_angle += ROTATION_OFFSET;
		if (texture != animations[ANIM_WALK].first) {
			useAnimation(ANIM_WALK);
		}
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


void Player::captured(){
	attr->setAttribute(PLAYER_CAPTURED, attr->getAttribute(PLAYER_CAPTURED) + 1);
	if ( attr->getAttribute(PLAYER_LIVES) > 0 ){
		attr->setAttribute(PLAYER_LIVES, attr->getAttribute(PLAYER_LIVES) - 1);
	}
	useAnimation(ANIM_NONE);
	attr->setAttribute(ALIVE, 0); //deactivate. game will reactivate.
	attr->setAttribute(DAWG_PLAYER_CAPTURED, 1); // omg!!11!  set id to player ID maybe? leave 1 for now.
	
	vector<tile*> pTiles;
	point det = point(0,0); //front load
	pTiles = _pMap->zones[0]->getTiles(DETENTION_POINT); //todo: get current zone.
	
	if (pTiles.size() > 0){
		det = pTiles[0]->center();
	}
	xy(det);
	_target = point(_x, _y);
	attr->setAttribute(ALIVE, 1);
	
}
