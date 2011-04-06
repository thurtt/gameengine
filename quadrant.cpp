/*
 *  quadrant.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/11/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "quadrant.h"
#include "collision.h"


quad::quad(int _id, int _zone_id){
	id = _id; zone_id = _zone_id;
	height = QUADHEIGHT;
	width = QUADWIDTH;
	x = (id % 2) * QUADWIDTH + (zone_id % 4) * ZONEWIDTH ;
	y = (id / 2) * QUADHEIGHT + (zone_id / 4) * ZONEHEIGHT ;
	int i; 
	for (i = 0; i < QUADTILES; i++){
		tiles.push_back( new tile( i, id, zone_id ));
	}
}
quad::~quad(){
	int i;
	for (i = 0; i < tiles.size(); i++){
		delete tiles[i];
	}
}
void quad::draw(){
	draw(0.0f, 0.0f);
}

void quad::draw(float offset_x, float offset_y){
	if (onscreen(x + offset_x, y + offset_y, height, width) == false)
		return;
	
	int i;
	for (i = 0; i < tiles.size(); i++){
		tiles[i]->draw(offset_x, offset_y);
	}
}

void quad::animate(float offset_x, float offset_y){
	if (onscreen(x + offset_x, y + offset_y, height, width) == false)
		return;
	int i;
	for (i = 0; i < tiles.size(); i++){
		tiles[i]->animate(offset_x, offset_y);
	}
}

tile* quad::getTile(float world_x, float world_y)
{
	if (!inBox(world_x, world_y, x, y, x + width, y + height))
		return 0;
	
	tile* pTile;
	pTile = 0;
	int i;
	for (i = 0; i < tiles.size(); i++){
		if (inBox(world_x, world_y, tiles[i]->x, tiles[i]->y, tiles[i]->height, tiles[i]->width)){
			return tiles[i];
		}
	}
	
	return pTile;
}

vector<tile*> quad::getTiles(float box_x1, float box_y1, float box_x2, float box_y2)
{
	vector<tile*> pTile;
	int i;
	bool t1, t2;
	t1 = boxCollision( x, y, x + width, y + height, box_x1, box_y1, box_x2, box_y2 );
	t2 = boxCollision( box_x1, box_y1, box_x2, box_y2 , x, y, x + width, y + height );
	
	if ( !boxCollision( x, y, x + width, y + height, box_x1, box_y1, box_x2, box_y2 )  &&
		!boxCollision( box_x1, box_y1, box_x2, box_y2, x, y, x + width, y + height ) )
		return pTile;
	
	for (i = 0; i < tiles.size(); i++){
		
		if ( boxCollision(tiles[i]->x, tiles[i]->y,tiles[i]->x + tiles[i]->width, tiles[i]->y + tiles[i]->height, box_x1, box_y1, box_x2, box_y2)  ||
			boxCollision(box_x1, box_y1, box_x2, box_y2, tiles[i]->x, tiles[i]->y,tiles[i]->x + tiles[i]->width,tiles[i]->y + tiles[i]->height) )
		{
			pTile.push_back( tiles[i] );
		}
	}
	
	return pTile;
}

vector<tile*> quad::getTiles(int attribute)
{
	vector<tile*> pTile;
	int i;
	int spIter;
	int token; //easier to prevent duplicate entries.
	
	for (i = 0; i < tiles.size(); i++){
		//each tile has sprites.
		token = 0;
		for (spIter = 0; spIter < tiles[i]->sprites.size(); spIter++){
			if (tiles[i]->sprites[spIter]->attr->getAttribute(attribute) > 0 ){
				token += 1; //flag for keeping
			}
		}
		if (token > 0)
			pTile.push_back( tiles[i] );
	}
	
	return pTile;
}

