/*
 *  zone.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/11/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "zone.h"
#include "collision.h"


zone::zone(int _id){
	id = _id;
	height = ZONEHEIGHT;
	width = ZONEWIDTH;
	x = (id % 4) * ZONEWIDTH;
	y = (id / 4) * ZONEHEIGHT;
	int i; 
	for (i = 0; i < 4; i++){
		quads.push_back(new quad( i, id ));
	}
}
zone::~zone(){
	int i;
	for (i = 0; i < quads.size(); i++){
		delete quads[i];
	}
}

void zone::draw(float offset_x, float offset_y){
	if (onscreen(x + offset_x, y + offset_y, height, width) == false)
		return;
	int i;
	for (i = 0; i < quads.size(); i++){
		quads[i]->draw(offset_x, offset_y);
	}
}

void zone::draw(){
	draw(0.0f, 0.0f);
}

void zone::animate(float offset_x, float offset_y){
	if (onscreen(x + offset_x, y + offset_y, height, width) == false)
		return;
	int i;
	for (i = 0; i < quads.size(); i++){
		quads[i]->animate(offset_x, offset_y);
	}
}
tile* zone::getTile(float world_x, float world_y)
{
	if (!inBox(world_x, world_y, x, y, x + width, y + height))
		return 0;
	
	tile* pTile;
	pTile = 0;
	int i;
	for (i = 0; i < quads.size(); i++){
		pTile = quads[i]->getTile(world_x, world_y);
		if (pTile != 0) {
			return pTile;
		}
	}
	return pTile;
}

vector<tile*> zone::getTiles(float box_x1, float box_y1, float box_x2, float box_y2)
{
	vector<tile*> pTile;
	vector<tile*> temp_tile;
	int i;
	
	if ( !boxCollision( x, y, x + width, y + height, box_x1, box_y1, box_x2, box_y2 )  &&
		!boxCollision( box_x1, box_y1, box_x2, box_y2, x, y, x + width, y + height ) )
		return pTile;

	
	for (i = 0; i < quads.size(); i++){
		temp_tile = quads[i]->getTiles(box_x1, box_y1, box_x2, box_y2);
		if (temp_tile.size() > 0)
			pTile.insert( pTile.end(),temp_tile.begin(), temp_tile.end());
	}
	
	return pTile;
}


vector<tile*> zone::getTiles(int attribute)
{
	vector<tile*> pTile;
	vector<tile*> temp_tile;
	int i;
	
	for (i = 0; i < quads.size(); i++){
		temp_tile = quads[i]->getTiles(attribute);
		if (temp_tile.size() > 0)
			pTile.insert( pTile.end(),temp_tile.begin(), temp_tile.end());
	}
	
	return pTile;
}

vector<tile*> zone::getTiles()
{
	vector<tile*> tempTiles;
	for ( int i = 0; i < quads.size(); i++ ) 
	{
		tempTiles.insert( tempTiles.end(), quads[i]->getTiles().begin(), quads[i]->getTiles().end() );
	}
	
	return tempTiles;
}