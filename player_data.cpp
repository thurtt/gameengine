/*
 *  player_data.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 2/27/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "player_data.h"


player_data::player_data(const char * _name, const char * _tex, point _spawn, point _hw) : spawn(_spawn), name(_name), texture(_tex)
{
	height = _hw.x;
	width = _hw.y;
}