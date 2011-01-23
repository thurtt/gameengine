/*
 *  player.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/23/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "player.h"

#include "los.h"
#include "text.h"

Player::Player( float _x_, float _y_, float _width_, float _height_, const char * _filename,  std::vector<game_sprite*> * sprites ) :
_los(0),
_text(0)
{
	// do some basic setup
	
	xy(_x_, _y_);
	wh(_width_, _height_);
	texture_file = _filename;
	_blockMovement = false;
	_blockVisibility = false;
	
	texture = LoadTexture(texture_file);
	textures.push_back( texture );
	includeAnimation(ANIM_NONE, texture, 0);
	includeAnimation(ANIM_EXPLODE, "explosion.png", 25);
	includeAnimation(ANIM_WALK, "player_walking_64.png", 8);
	useAnimation(ANIM_NONE);
	
	_los = new line_of_sight( 180.0, 250.0, 64, 64, sprites );
	setDrawable( _los );
	
	_text = new Text();
	setDrawable( _text );	
}

Player::~Player()
{
	// this is a wee bit dangerous
	delete _los;
	_los = 0;
	
	delete _text;
	_text = 0;
}

