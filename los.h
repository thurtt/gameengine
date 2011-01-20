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

class line_of_sight : public drawable
{
public:
	
	// has to be overridden
	virtual void draw( float x, float y, float angle );
	
	// field of vision, depth of vision
	line_of_sight( float fov, float dov );
	
	bool IsTargetVisible( float target_x, float target_y );
private:
	line_of_sight();
	line_of_sight( const line_of_sight& );
	const line_of_sight& operator=( const line_of_sight& );
	
	
	float _fov;
	float _dov;
	
	std::vector< std::pair< float, float > > _box_coords;
};
 #endif // _LOS_H_

