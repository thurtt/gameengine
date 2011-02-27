/*
 *  quadrant.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/11/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "tiles.h"

#include <vector>
#include <string>
using namespace std;

class quad{
public:
	float x, y;
	float height, width;
	int id, zone_id;
	bool populated;
	vector<tile*> tiles;
	quad(int _id, int _zone_id);
	~quad();
	void draw();
	void draw(float, float);
	void animate(float, float);
	tile* getTile(float world_x, float world_y);
	vector<tile*> getTiles(float box_x1, float box_y1, float box_x2, float box_y2);
	vector<tile*> getTiles(int attribute);
};