/*
 *  los.h
 *  gltest
 *
 *  Created by tom on 1/15/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _LOS_H_
#define _LOS_H_


#include "drawable.h"
#include <utility>
#include <vector>
#include "sprite.h"
#include "line.h"

class line_of_sight : public drawable
{
public:
	
	// has to be overridden
	virtual void draw( float x, float y, float angle );
	
	// field of vision, depth of vision, height and width are required
	line_of_sight( float fov, float dov, float height, float width, std::vector<game_sprite*> * sprites );
	
	std::vector<point> detect_visible_sprites();
private:
	line_of_sight();
	line_of_sight( const line_of_sight& );
	const line_of_sight& operator=( const line_of_sight& );

	bool in_my_box( float x, float y, float h, float w );
	
	// returns x,y prime, where orig is the point to rotate around, and point is the point to rotate
	point rotate( float point_x, float point_y, float orig_x, float orig_y, float angle );
	
	float _fov;
	float _dov;
	float _height;
	float _width;
	float _angle;
	polygon _corners;

	std::vector<game_sprite*> * _sprites;
};

 #endif // _LOS_H_

