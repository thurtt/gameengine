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
	int bMovement;
	int bVisibility;
	_sprite_data(float, float, float, float, const char *, int, int);
};



#endif