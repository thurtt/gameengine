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

#include "tile_defines.h"

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

const float FIELD_OF_VISION = 180.0;
const float DEPTH_OF_VISION = 250.0;

class game_sprite {
protected:
	const char * texture_file;
	vector<GLuint> textures; 
	GLuint texture;
	map<int, GLuint> animations;
public:
	bool _blockVisibility;
	bool _blockMovement;
	int width, height;
	float _x; float _y;
	float _angle;
	bool use_los;
	int move_left; int move_right; int move_up; int move_down;
	int frame;
	game_sprite();
	game_sprite(float, float, float, float, const char *, bool, bool);
	~game_sprite();
	void includeAnimation(int, GLuint);
	void includeAnimation(int, char *);
	void useAnimation(int);
	void animate();
	virtual void movement();
	bool blockVisibility();
	void blockVisibility(bool);
	bool blockMovement();
	void blockMovement(bool);
	void xy(float, float);
	void wh(float, float);
	void draw();
	void draw(float, float);
	void draw_fov( float ref_x, float ref_y );
	void rotate( float angle );
	void text(char *str);
	GLuint LoadTexture( const char * filename);
	void renderSpacedBitmapString(float x, float y, int spacing, void *font, char *str);
};


#endif