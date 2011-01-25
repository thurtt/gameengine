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

bool inBox(float x, float y, float box_x, float box_y, float box_h, float box_w);
bool boxCollision(float x, float y, float h, float w, float box_x, float box_y, float box_h, float box_w);
bool onscreen(float x, float y, float height, float width);

#endif // _COLLISION_H_
