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

bool inBox(float x, float y, float box_x, float box_y, float box_h, float box_w);
bool boxCollision(float x, float y, float h, float w, float box_x, float box_y, float box_h, float box_w);
bool polygonCollision( const std::vector< std::pair<float, float> > & poly1, const std::vector< std::pair<float, float> > & poly2 );
bool lineCompare(  std::pair< std::pair< float, float >, std::pair< float, float > > line1, float slope1, std::pair< std::pair< float, float >, std::pair< float, float > > line2, float slope2 );
bool sort_predicate( const std::pair<float, float> & left, const std::pair<float, float> & right );
bool onscreen(float x, float y, float height, float width);

#endif // _COLLISION_H_
