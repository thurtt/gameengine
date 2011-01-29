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

	bool result = ( ( y < max<float>( box_y1, box_y2 ) )
			&& ( y > min<float>( box_y1, box_y2 ) )
			&& ( x < max<float>( box_x1, box_x2 ) )
			&& ( x > min<float>( box_x1, box_x2 ) ) );
	
	return result;
	//return ((y < box_y + box_h) && (x < box_x + box_w) && (y > box_y) && ( x > box_x));
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
	
	return ( boxCollision(x,y,x+width,y+height,0,0,windowHeight, windowWidth) ||
			boxCollision(0,0, windowWidth, windowHeight, x, y, x+width, y+height));
}


bool polygonCollision( polygon & poly1, polygon & poly2 )
{
	polyIterator itr1 = poly1.begin();
	
	while( itr1 != poly1.end() )
	{
		polyIterator itr2 = poly2.begin();
		while( itr2 != poly2.end() )
		{
			if ( itr1->checkIntersection( *itr2 ) )
			{
				return true;
			}
			++itr2;
		}
		++itr1;
	}	
	return false;
}

/*
bool lineCompare( std::pair< std::pair< float, float >, std::pair< float, float > > line1, float slope1, std::pair< std::pair< float, float >, std::pair< float, float > > line2, float slope2 )

{
	// short circuit case
	if ( slope1 == slope2 )
	{
		return false;
	}
	
	// get the equation for each line
	// the equation is y = a + bx
	// we know x, y, and b, so we need a
	// algebra says: -a = -y + bx or a = y - bx
	// so lets rock this shit.
	float a1 = line1.first.second - ( slope1 * line1.first.first );
	float a2 = line2.first.second - ( slope2 * line2.first.first );
	
	// solve the simultaneous linear equation
	// xi = -(a1 - a2)/(b1 -b2)yi 
	// yi = a1 + b1xi
	// substitution
	// xi = -(a1 - a2)/(b1-b2)(a1 + b1xi)
	// it reduces to xi = a1( (-(a1 - a2)/(b1 -b2)) -(1/b1) )
	float x_intersect = a1 * ( (-(a1 - a2)/(slope1 - slope2) ) - (1/slope1) );
	float y_intersect = a1 + ( slope1 * x_intersect );
	
	// check to see if the intersects are on the segments
	// (x1 - xi) (xi - x2) >= 0
	if ( ( ( line1.first.first - x_intersect ) * ( x_intersect - line1.second.first ) ) >= 0 )
	{
		return true;
	}
	if ( ( ( line1.first.second - y_intersect ) * ( y_intersect - line1.second.second ) ) >= 0 )
	{
		return true;
	}	
	
	return false;

}*/









