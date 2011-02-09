/*
 *  game_map.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/28/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */


#include "game_map.h"

game_map::game_map()
{
}

game_map::game_map(int _map)
{
	loadMap(_map);
}

game_map::~game_map()
{
	int i;
	for (i = 0; i < zones.size(); i++){
		delete zones[i];
	}
}

void game_map::animate(int offset_x, int offset_y)
{
	int i;
	for (i = 0; i < zones.size(); i++){
		zones[i]->animate( offset_x, offset_y );
	}
}

void game_map::draw(int offset_x, int offset_y)
{
	int i;
	for (i = 0; i < zones.size(); i++){
		zones[i]->draw( offset_x, offset_y );
	}
}

void game_map::loadMap(int _map)
{
	// map is series of zones
	genTiles();
	
	int i;
	for ( i = 0; i < 16; i++){
		zones.push_back( new zone( i ) );
	}
}

void game_map::clearMap()
{
	zones.clear();
}

void game_map::genTiles()
{
	populateTileSet();
}

tile* game_map::getTile(float world_x, float world_y)
{
	tile* pTile;
	pTile = 0;
	int i;
	
	for (i = 0; i < zones.size(); i++){
		pTile = zones[i]->getTile( world_x, world_y );
		if (pTile != 0) {
			return pTile;
		}
	}
	return pTile;
}

vector<tile*> game_map::getTiles(float x1, float y1, float x2, float y2)
{
	vector<tile*> pTile;
	vector<tile*> temp_tile;
	int i;
	for (i = 0; i < zones.size(); i++){
		temp_tile = zones[i]->getTiles(x1, y1, x2, y2);
		if (temp_tile.size() > 0)
			pTile.insert( pTile.end(),temp_tile.begin(), temp_tile.end());
	}
	
	return pTile;
}

