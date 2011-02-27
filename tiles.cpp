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


int zone_1[ZONETILES] =	{
	6,5,5,5,5,4,2,3,3,5,
	4,1,1,1,1,4,2,2,2,2,
	7,1,1,5,5,2,2,2,2,2};
int zone_2[ZONETILES] = {1};
int zone_EMPTY[ZONETILES] = {0};

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
	
	for (i = 0; i < tileset[tile_id].size(); i++){
		sprites.push_back( new game_sprite( x, y, tileset[tile_id][i] ) );
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
point tile::center(){
	return point(x + ( width / 2), y + ( height / 2));
}

float tile::distance(point target){
	return sqrt( pow(target.x - x, 2) + pow(target.y - y, 2) );
}

void populateTileSet(){
	tileset.clear();
	
	vector<_sprite_data*> raw_tile ;
	raw_tile.push_back( new _sprite_data(0,0,TILESIZE,TILESIZE,"clean_tiles.png", 0, 0, 0, 0));
	tileset.push_back(raw_tile);
	
	vector<_sprite_data*> raw_tile2 ;
	raw_tile2.push_back( new _sprite_data(0,0,TILESIZE,TILESIZE,"clean_tiles.png", 0, 0, 0, 0));
	tileset.push_back(raw_tile2);
	
	
	vector<_sprite_data*> raw_tile3 ;
	raw_tile3.push_back( new _sprite_data(0,0,TILESIZE,TILESIZE,"grass.png", 0, 0, 0, 0));	
	tileset.push_back(raw_tile3);
	
	vector<_sprite_data*> raw_tile4 ;
	raw_tile4.push_back( new _sprite_data(0,0,TILESIZE,TILESIZE,"clean_tiles.png", 1, 1, 0, 0)); //this will blockmovement.
	raw_tile4.push_back( new _sprite_data(0,0,TILESIZE,TILESIZE,"tile_blood.png", 0, 0, 0, 0));
	tileset.push_back(raw_tile4);
	
	
	/* verticle wall*/
	vector<_sprite_data*> raw_tile5 ;
	raw_tile5.push_back( new _sprite_data(0,0,TILESIZE,TILESIZE,"clean_tiles.png", 0, 0, 0, 0));
	raw_tile5.push_back( new _sprite_data(0,0,TILESIZE,15,"wall.png", 1, 1, 0, 0)); //this will blockmovement.
	tileset.push_back(raw_tile5);
	
	/* horizontal wall*/
	vector<_sprite_data*> raw_tile6 ;
	raw_tile6.push_back( new _sprite_data(0,0,TILESIZE,TILESIZE,"clean_tiles.png", 0, 0, 0, 0));
	raw_tile6.push_back( new _sprite_data(0,0,15,TILESIZE,"wall.png", 1, 1, 0, 0)); //this will blockmovement.
	tileset.push_back(raw_tile6);
	
	
	/* corner wall*/
	vector<_sprite_data*> raw_tile7 ;
	raw_tile7.push_back( new _sprite_data(0,0,TILESIZE,TILESIZE,"clean_tiles.png", 0, 0, 0, 0));
	raw_tile7.push_back( new _sprite_data(0,0,15,TILESIZE,"wall.png", 1, 1, 0, 0)); //this will blockmovement.
	raw_tile7.push_back( new _sprite_data(0,0,TILESIZE,15,"wall.png", 1, 1, 0, 0)); //this will blockmovement.
	tileset.push_back(raw_tile7);	
	
	
	/* corner wall SPAWN */
	vector<_sprite_data*> raw_tile8 ;
	raw_tile8.push_back( new _sprite_data(0,0,TILESIZE,TILESIZE,"clean_tiles.png", 0, 0, 1, 0));
	raw_tile8.push_back( new _sprite_data(0,0,15,TILESIZE,"wall.png", 1, 1, 0, 0)); //this will blockmovement.
	raw_tile8.push_back( new _sprite_data(0,0,TILESIZE,15,"wall.png", 1, 1, 0, 0)); //this will blockmovement.
	tileset.push_back(raw_tile8);
}
