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

class LineOfSight
{
public:
	// field of vision, depth of vision
	LineOfSight( float fov, float dov );
	
	bool IsTargetVisible( float target_x, float target_y );
private:
};

#endif // _LOS_H_

