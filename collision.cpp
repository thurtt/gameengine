/*
 *  collision.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/22/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "collision.h"

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


bool inBox(float x, float y, float box_x, float box_y, float box_h, float box_w){
	return ((y < box_y + box_h) && (x < box_x + box_w) && (y > box_y) && ( x > box_x));
}
bool boxCollision(float x, float y, float h, float w, float box_x, float box_y, float box_h, float box_w){
	return (inBox(x,y,box_x,box_y,box_h,box_w) ||
			inBox(x + w,y,box_x,box_y,box_h,box_w) ||
			inBox(x,y + h,box_x,box_y,box_h,box_w) ||
			inBox(x + w,y + h,box_x,box_y,box_h,box_w));
}
bool onscreen(float x, float y, float height, float width){
	int windowHeight = glutGet( GLUT_WINDOW_HEIGHT );
	int windowWidth = glutGet( GLUT_WINDOW_WIDTH );
	
	return ( boxCollision(x,y,height,width,0,0,windowHeight, windowWidth) ||
			boxCollision(0,0,windowHeight, windowWidth,x,y,height,width));
}
