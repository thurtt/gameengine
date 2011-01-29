/*
 *  tiles.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/11/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "tiles.h"
#include "collision.h"


int zone_1[ZONETILES] =	{1,2,2,2,2,
	2,2,3,3,2,
	2,2,3,3,2,
	2,2,2,2,2,
	2,2,2,2,2};
 int zone_2[ZONETILES] = {1};

 int * map_1[16] = { zone_1, zone_1, zone_1, zone_1,
					zone_1, zone_1, zone_1, zone_1,
					zone_1, zone_1, zone_1, zone_1,
					zone_1, zone_1, zone_1, zone_1};

 int ** maps[1] = { map_1 };


vector< vector<_sprite_data*> > tileset;


tile::tile(int _id, int _quad_id, int _zone_id){
	id = _id; zone_id = _zone_id; quad_id = _quad_id;
	height = TILESIZE;
	width = TILESIZE;
	
	x = (id % (TILESETWIDTH / 2) ) * TILESIZE + ((quad_id % 2) * QUADWIDTH + (zone_id % 4) * ZONEWIDTH) ;
	y = (id / (TILESETHEIGHT / 2) ) * TILESIZE + ((quad_id / 2) * QUADHEIGHT + (zone_id /4) * ZONEHEIGHT) ;
	int i; 
	int tile_id = maps[0][zone_id][quad_id * QUADTILES + id];
	int tilesize = tileset[tile_id].size();
	
	for (i = 0; i < tileset[tile_id].size(); i++){
		sprites.push_back( new game_sprite( tileset[tile_id][i]->x + x, 
										   tileset[tile_id][i]->y + y,  
										   tileset[tile_id][i]->width,
										   tileset[tile_id][i]->height,
										   tileset[tile_id][i]->texture,
										   tileset[tile_id][i]->bVisibility,
										   tileset[tile_id][i]->bMovement));
	}
}
tile::~tile(){
	int i;
	for (i = 0; i < sprites.size(); i++){
		delete sprites[i];
	}
}

void tile::draw(){	
	draw(0.0f, 0.0f);
}


void tile::draw(float offset_x, float offset_y){	
	if (sprites.size() == 0)
		return;
	
	if (onscreen(x + offset_x, y + offset_y, height, width) == false)
		return;
	int i; 
	for (i = 0; i < sprites.size(); i++){
		sprites[i]->draw(offset_x, offset_y);
	}
}
void tile::animate(float offset_x, float offset_y){
	if (onscreen(x + offset_x, y + offset_y, height, width) == false)
		return;
	int i;
	for (i = 0; i < sprites.size(); i++){
		sprites[i]->animate();
	}
}

void populateTileSet(){
	tileset.clear();
	
	vector<_sprite_data*> raw_tile ;
	raw_tile.push_back( new _sprite_data(0,0,TILESIZE,TILESIZE,"clean_tiles.png", false, false));
	tileset.push_back(raw_tile);
	
	vector<_sprite_data*> raw_tile2 ;
	raw_tile2.push_back( new _sprite_data(0,0,TILESIZE,TILESIZE,"clean_tiles.png", false, false));
	tileset.push_back(raw_tile2);
	
	
	vector<_sprite_data*> raw_tile3 ;
	raw_tile3.push_back( new _sprite_data(0,0,TILESIZE,TILESIZE,"grass.png", false, false));	
	tileset.push_back(raw_tile3);
	
	vector<_sprite_data*> raw_tile4 ;
	raw_tile4.push_back( new _sprite_data(0,0,TILESIZE,TILESIZE,"clean_tiles.png", true, true)); //this will blockmovement.
	raw_tile4.push_back( new _sprite_data(0,0,TILESIZE,TILESIZE,"tile_blood.png", false, false));
	tileset.push_back(raw_tile4);
}
