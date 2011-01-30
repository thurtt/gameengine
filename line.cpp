#include "line.h"
#include <algorithm>
#include <math.h>
using namespace std;

float line::getSlope() const
{
	// rise over run, bitches
	// vertical lines will return an FPE
	return (_y1 - _y2) / (_x1 - _x2);
}

point line::checkIntersection( const line & line2 ) const
{
	// now the real work begins

	// lets try this using determinants
	// converting to form Ax + By = C
	float A1 = _y2 - _y1;
	float B1 = _x1 - _x2;
	float C1 = ( A1 * _x1 ) + ( B1 * _y1 );

	float A2 = line2.getPoint2().y - line2.getPoint1().y;
	float B2 = line2.getPoint1().x - line2.getPoint2().x;
	float C2 = ( A2 * line2.getPoint1().x ) + ( B2 * line2.getPoint1().y );

	float det = ( A1 * B2 ) - ( A2 * B1 );
	
	// parallel test
	if ( det == 0 ) point( 0, 0 );

	float x_intersect = ( ( B2 * C1 ) - ( B1 * C2 ) ) / det;
	float y_intersect = ( ( A1 * C2 ) - ( A2 * C1 ) ) / det;

	return point( x_intersect, y_intersect );
}

bool line::isPointOnLine( const point & testPoint ) const
{
	if( testPoint.x <= max<float>( _x1, _x2 ) && testPoint.x >= min<float>( _x1, _x2 )
	   && testPoint.y <= max<float>( _y1, _y2 ) && testPoint.y >= min<float>( _y1, _y2 ) )
	{
		return true;
	}
	return false;
}
