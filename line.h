#ifndef _LINE_H_
#define _LINE_H_
#include <vector>

struct point
{
	point( float _x, float _y ): x(_x), y(_y){}
	point( const point & newPoint ) : x(newPoint.x), y(newPoint.y) {}
	point & operator=( point rhs )
	{
		// check for self assignment
		if( this != &rhs )
		{
			x = rhs.x;
			y = rhs.y;
		}
		return *this;
	}
	
	bool operator==( const point & rhs ){ return( rhs.x == x && rhs.y == y ); }
	
	float x;
	float y;
};

class line
{
public:
	line( float x1, float y1, float x2, float y2 ): _x1(x1), _y1(y1), _x2(x2), _y2(y2){}
	line( point point1, point point2 ): _x1(point1.x), _y1(point1.y), _x2(point2.x), _y2(point2.y){}
	
	point getPoint1() const { return point( _x1, _y1 ); }
	point getPoint2() const { return point( _x2, _y2 ); }
	float getSlope() const;
	point checkIntersection( const line & line2 ) const;
	bool isPointOnLine( const point & testPoint ) const;
	bool isHorizontal() const { return _y1 == _y2; }
	bool isVertical() const { return _x1 == _x2; }

private:
	float _x1;
	float _y1;
	float _x2;
	float _y2;
};

typedef std::vector<line> polygon;
typedef std::vector<line>::iterator polyIterator;

#endif // _LINE_H_