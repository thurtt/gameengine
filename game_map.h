/*
 *  game_map.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/28/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */
#ifndef _GAMEMAP_H_
#define _GAMEMAP_H_


#include "zone.h"

#include "waypoints.h"
#include "line.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

class game_map{
public:
	vector<zone*> zones;
	vector<game_sprite *> markers;
	game_map();
	game_map(int _map);
	~game_map();
	void animate(int offset_x, int offset_y);
	void draw(int offset_x, int offset_y);
	void loadMap(int _map);
	void clearMap();
	void genTiles();
	void PlaceMarker(point _xy);
	tile* getTile(float world_x, float world_y);
	vector<tile*> getTiles(float x1, float y1, float x2, float y2);
	vector<tile*> getTiles(int attribute);
};

#endif // _GAMEMAP_H_