/*
 *  rotation.h
 *  gltest
 *
 *  Created by tom on 1/30/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _ROTATION_H_
#define _ROTATION_H_

#include "line.h"

// returns x,y prime, where orig is the point to rotate around, and point is the point to rotate
point rotate( float point_x, float point_y, float orig_x, float orig_y, float angle );

float toDegrees( float radians );
float toRadians( float radians );

#endif // _ROTATION_H_

