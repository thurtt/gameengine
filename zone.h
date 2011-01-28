/*
 *  zone.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/11/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */
#ifndef ZONE_H
#define ZONE_H

#include "quadrant.h"
#include <vector>
#include <string>
using namespace std;

class zone{
public:
	float x, y;
	float height, width;
	int id;
	bool populated;
	vector<quad*> quads;
	zone(int _id);
	~zone();
	void draw();
	void draw(float, float);
	void animate(float, float);
	tile* getTile(float world_x, float world_y);
};



#endif