/*
 *  sprite_data.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/11/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "sprite_data.h"


_sprite_data::_sprite_data(float _x, float _y, float _height, float _width, const char * _texture, int vis, int mov){
	x = _x; y = _y;
	height = _height; width = _width;
	texture = _texture;
	bMovement = mov;
	bVisibility = vis;
};
