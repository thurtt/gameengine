/*
 *  player_data.h
 *  gltest
 *
 *  Created by Stuart Templeton on 2/27/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#ifndef _PLAYERDATA_H_
#define _PLAYERDATA_H_

#include "line.h"

#include <vector>
#include <string>

class player_data {
public:
	player_data(const char * _name, const char * _tex, point _spawn, point _hw);
	
	point spawn;
	int height;
	int width;
	const char * name;
	const char * texture;
};

#endif