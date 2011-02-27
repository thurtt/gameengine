/*
 *  sprite.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/8/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#ifndef SPRITE_H
#define SPRITE_H

#include "sprite_defines.h"
#include "tile_defines.h"
#include "drawable.h"
#include "spriteAttribute.h"
#include "sprite_data.h"
#include "line.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>
#include <utility>
#include <map>

#ifdef WIN32
#include <freeglut.h>
#elif defined(__APPLE__) || defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GLUT/glut.h>
#endif

using namespace std;


class game_sprite {
protected:
	const char * texture_file;
	GLuint texture;
	map<int, pair<GLuint, int> > animations;
	vector<game_sprite *>  sprite_list;
	
	vector<drawable *> drawables; // need to think about who is responsible for cleaning this up.
	
public:

	spriteAttribute * attr;
	bool active;
	int width, height;
	float _x; float _y;
	float _angle;
	int move_left; int move_right; int move_up; int move_down;
	int frame;
	float disp_x;
	float disp_y;
	game_sprite();
	game_sprite(float _x_, float _y_, _sprite_data * sprite_data);
	game_sprite(float, float, float, float, const char *, int, int);
	~game_sprite();
	void generalInit(float _x_, float _y_, float _width_, float _height_, const char * _filename, int vis, int mov);
	void includeAnimation(int, GLuint, int);
	void includeAnimation(int,const char *, int);
	void useAnimation(int);
	void xy(point pt);
	void xy(float, float);
	void wh(float, float);
	void draw();
	virtual void draw (float, float);
	virtual int click (int, int, int);
	virtual void animate();
	virtual void movement();
	void text(char *str);
	GLuint LoadTexture( const char * filename);
	void renderSpacedBitmapString(float x, float y, int spacing, void *font, char *str);
	void setDrawable( drawable * pDrawable );
	void includeSprite( game_sprite * pSprite );
	float distance(point target);
	point center();
};

void texture_cleanup(); //clean up straggler textures

/**************
 Sort routine for vectors of these bitches.
 **************/
struct by_distance {
	by_distance(point _t) : target(_t) {}
	bool operator()(game_sprite &a, game_sprite &b) {
		return a.distance(target) < b.distance(target);
	}
	point target;
};
//use: std::sort(sprites.begin, sprites.end, by_distance( point(my_x, my_y)));

#endif