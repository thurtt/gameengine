/*
 *  game.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/9/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#ifndef GAME_H
#define GAME_H

#include "sprite.h"
#include "input.h"
#include "zone.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

#ifdef WIN32
#include <freeglut.h>
#elif defined(__APPLE__) || defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GLUT/glut.h>
#endif


using namespace std;

class game{
	
	vector<game_sprite*> sprites;
	int frame,time,timebase;
	float offset_x;
	float offset_y;
public:
	game_sprite* focus_sprite;
	vector<zone*> zones;
	bool _finished;
	game();
	~game();
	void draw();
	void movement();
	void animate();
	void init();
	void idle();
	
	bool finished();
	bool finished(bool);
	void genTiles();
	void loadMap(int map);
	
};
#endif