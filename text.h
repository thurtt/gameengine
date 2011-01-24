#ifndef _TEXT_H_
#define _TEXT_H_

#include "drawable.h"

const unsigned long MAX_CHARS = 2048;
const int CHAR_WIDTH = 6;

class Text : public drawable
{
public:
	Text();
	~Text();
	void draw( float x, float y, float angle );
	void printf( const char * fmt, ... );

private:
	char * _msg;

	void write_string( float x, float y );

};
	

#endif // _TEXT_H_