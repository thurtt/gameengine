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
#include "line.h"
#include "map_manager.h"

#include <math.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class tile{
public:
	float x, y;
	float height, width;
	int id, quad_id, zone_id;
	tile(int _id, int _quad_id, int _zone_id, vector<SpriteObject> & spriteObjects );
	~tile();
	void draw();
	void draw(float, float);
	void animate(float, float);
	point center();
	float distance(point target);
	vector<game_sprite*> sprites;
};

void populateTileSet();


/**************
 Sort routine for vectors of these bitches.
 **************/
struct by_tile_distance {
	by_tile_distance(point _t) : target(_t) {}
	bool operator()(tile &a, tile &b) {
		return a.distance(target) < b.distance(target);
	}
	point target;
};
//use: std::sort(tiles.begin, tiles.end, by_tile_distance( point(my_x, my_y)));

#endif // _TILES_H_
