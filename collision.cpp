/*
 *  collision.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/22/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#ifdef WIN32
#include <freeglut.h>
#elif defined(__APPLE__) || defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "collision.h"
#include <algorithm>

using namespace std;

bool inBox(float x, float y, float box_x1, float box_y1, float box_x2, float box_y2){
	return ( ( y < max<float>( box_y1, box_y2 ) )
			&& ( y > min<float>( box_y1, box_y2 ) )
			&& ( x < max<float>( box_x1, box_x2 ) )
			&& ( x > min<float>( box_x1, box_x2 ) ) );
}

bool boxCollision(float x1, float y1, float x2, float y2, float box_x1, float box_y1, float box_x2, float box_y2){
	return (inBox(x1,y1,box_x1,box_y1,box_x2,box_y2) ||
			inBox(x2,y2,box_x1,box_y1,box_x2,box_y2) ||
			inBox(x1,y2,box_x1,box_y1,box_x2,box_y2) ||
			inBox(x2,y2,box_x1,box_y1,box_x2,box_y2));
}
bool onscreen(float x, float y, float height, float width){
	int windowHeight = glutGet( GLUT_WINDOW_HEIGHT );
	int windowWidth = glutGet( GLUT_WINDOW_WIDTH );
	
	return ( boxCollision(x,y,x+width,y+height,0,0,windowWidth, windowHeight) ||
			boxCollision(0,0, windowWidth, windowHeight, x, y, x+width, y+height));
}


bool polygonCollision( polygon & poly1, polygon & poly2 )
{
	polyIterator itr1 = poly1.begin();
	int intersectionCount = 0;
	
	while( itr1 != poly1.end() )
	{
		polyIterator itr2 = poly2.begin();
		while( itr2 != poly2.end() )
		{
			point intersection = itr1->checkIntersection( *itr2 );
			if ( itr1->isPointOnLine( intersection ) )
			{
				intersectionCount++;
				if( intersectionCount >= 8 )
				{
					return true;
				}
			}
			++itr2;
		}
		++itr1;
	}	
	return false;
}

bool linePolyCollision( line & testLine, polygon & testPoly)
{
	// 2 intersections should be a collision
	polyIterator itr = testPoly.begin();
	int collCounter = 0;
	int pointCount = 1;
	while( itr != testPoly.end() )
	{
		point collPoint = testLine.checkIntersection( *itr );
		if ( testLine.isPointOnLine( collPoint ) )
		{
			collCounter++;
		}
		++itr;
		pointCount++;
	}

	if( collCounter > 1 )
	{
		return true;
	}
	return false;
}



