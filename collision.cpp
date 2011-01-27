/*
 *  collision.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/22/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "collision.h"

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


// each point in the list should connect to the previous point
// if a list is passed in that doesn't follow this model, things 
// won't work
bool polygonCollision( const std::vector< std::pair<float, float> > & poly1, const std::vector< std::pair<float, float> > & poly2 )
{
	// lets turn these points into lines
	std::vector< std::pair< std::pair<float, float>, std::pair<float, float> > > poly1Lines;
	std::vector< std::pair< std::pair<float, float>, std::pair<float, float> > > poly2Lines;	

	for ( unsigned long i = 0; i < poly1.size(); i++ )
	{
		if ( i < poly1.size() - 1 )
		{
			poly1Lines.push_back( std::pair< std::pair<float,float>, std::pair<float, float> >( poly1[i], poly1[i+1] ) );
		}
		else
		{
			poly1Lines.push_back( std::pair< std::pair<float,float>, std::pair<float, float> >( poly1[i], poly1[0] ) );		
		}
	}
	
	for ( unsigned long i = 0; i < poly2.size(); i++ )
	{
		if ( i < poly2.size() - 1 )
		{
			poly2Lines.push_back( std::pair< std::pair<float,float>, std::pair<float, float> >( poly2[i], poly2[i+1] ) );
		}
		else
		{
			poly2Lines.push_back( std::pair< std::pair<float,float>, std::pair<float, float> >( poly2[i], poly2[0] ) );		
		}
	}
	
	// compare the lines to eachother
	std::vector< std::pair< std::pair<float, float>, std::pair<float, float> > >::iterator itr1 = poly1Lines.begin();
	std::vector< std::pair< std::pair<float, float>, std::pair<float, float> > >::iterator itr2 = poly2Lines.begin();
	
	while( itr1 != poly1Lines.end() )
	{
		while( itr2 != poly2Lines.end() )
		{
			// rise over run, bitches
			float slope1 = ( (*itr1).first.second - (*itr1).second.second ) / ( (*itr1).first.first - (*itr1).second.first );
			float slope2 = ( (*itr2).first.second - (*itr2).second.second ) / ( (*itr2).first.first - (*itr2).second.first );	
			if ( lineCompare( *itr1, slope1, *itr2, slope2 ) == true )
			{
				return true;
			}
			++itr2;
		}
		++itr1;
	}
	
	return true;
}


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
	// it reduces to xi = a1( -((a1 - a2)/(b1 -b2)) -(1/b1) )
	float x_intersect = a1 * ( -( (a1 - a2)/(slope1 - slope2) ) -(1/slope1) );
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

}

bool sort_predicate( const std::pair<float, float> & left, const std::pair<float, float> & right )
{
	return left.first < right.first;
}








