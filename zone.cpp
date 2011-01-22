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