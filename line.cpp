#include "line.h"
#include <algorithm>
using namespace std;

float line::getSlope() const
{
	// rise over run, bitches
	// vertical lines will return an FPE
	return (_y1 - _y2) / (_x1 - _x2);
}

bool line::checkIntersection( const line & line2 ) const
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
	
	// we've already done a parallel test, but for safety
	if ( det == 0 ) return false;

	float x_intersect = ( ( B2 * C1 ) - ( B1 * C2 ) ) / det;
	float y_intersect = ( ( A1 * C2 ) - ( A2 * C1 ) ) / det;

	// check to see if the intersects are on the segments
	// it should lie somewhere between _x1 and _x2
	// also _y1 and _y1
	if ( ( x_intersect <= max<float>( _x1, _x2 ) && x_intersect >= min<float>( _x1, _x2 ) )
		&& ( y_intersect <= max<float>( _y1, _y2 ) && y_intersect >= min<float>( _y1, _y2 ) )
		&& ( x_intersect <= max<float>( line2.getPoint1().x, line2.getPoint2().x ) && x_intersect >= min<float>( line2.getPoint1().x, line2.getPoint2().x ) )
		&& ( y_intersect <= max<float>( line2.getPoint1().y, line2.getPoint2().y ) && y_intersect >= min<float>( line2.getPoint1().y, line2.getPoint2().y ) ) )
	{
		return true;
	}
	
	return false;
}
