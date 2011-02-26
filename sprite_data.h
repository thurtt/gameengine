/*
 *  sprite_data.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/11/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */
#ifndef SPDATA_H
#define SPDATA_H

#include "tile_defines.h"

#include <vector>
#include <string>

using namespace std;

class _sprite_data {
public:
	float x, y;
	float height, width;
	const char * texture;
	int Movement;
	int Visibility;
	int Spawn;
	int Detention;
	_sprite_data(float _x, float _y, float _height, float _width, const char * _texture, int vis, int mov, int spn, int det);
};



#endif