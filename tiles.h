/*
 *  tiles.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/11/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */
#ifndef _TILES_H_
#define _TILES_H_

#include "sprite_data.h"
#include "sprite.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class tile{
public:
	float x, y;
	float height, width;
	int id, quad_id, zone_id;
	tile(int _id, int _quad_id, int _zone_id);
	~tile();
	void draw();
	void draw(float, float);
	void animate(float, float);
	vector<game_sprite*> sprites;
};

void populateTileSet();

#endif // _TILES_H_
