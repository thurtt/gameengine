/*
 *  collision.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/22/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */
#ifndef _COLLISION_H_
#define _COLLISION_H_
#include <vector>
#include <utility>
#include "line.h"

bool inBox(float x, float y, float box_x1, float box_y1, float box_x2, float box_y2);
bool boxCollision(float x1, float y1, float x2, float y2, float box_x1, float box_y1, float box_x2, float box_y2);
bool polygonCollision( polygon & poly1, polygon & poly2 );
bool onscreen(float x, float y, float height, float width);
bool linePolyCollision( line & testLine, polygon & testPoly);


#endif // _COLLISION_H_
