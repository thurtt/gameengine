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
	markers.clear();
	
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
	
	for (i = 0; i < markers.size(); i++){
		markers[i]->animate();
	}
}

void game_map::draw(int offset_x, int offset_y)
{
	int i;
	for (i = 0; i < zones.size(); i++){
		zones[i]->draw( offset_x, offset_y );
	}
	
	for (i = 0; i < markers.size(); i++){
		//markers[i]->draw(0, 0);
		markers[i]->draw(offset_x, offset_y);
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

void game_map::PlaceMarker(point _xy)
{
	tile* pTile; //store the tile we clicked on.
	pTile = 0;
	
	pTile = getTile(_xy.x, _xy.y);
	
	if (pTile != 0){
		markers.clear(); //for now, just one at a time.
		markers.push_back(new game_sprite(pTile->x + (pTile->width / 2) - 16 ,pTile->y + (pTile->height / 2) - 16 , 32,32, "x_32.png", 0, 0));
	}
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


vector<tile*> game_map::getTiles(int attribute)
{
	vector<tile*> pTile;
	vector<tile*> temp_tile;
	int i;
	for (i = 0; i < zones.size(); i++){
		temp_tile = zones[i]->getTiles(attribute);
		if (temp_tile.size() > 0)
			pTile.insert( pTile.end(),temp_tile.begin(), temp_tile.end());
	}
	
	return pTile;
}
