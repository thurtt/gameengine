#ifndef _TEXT_H_
#define _TEXT_H_

#include "drawable.h"
#include <string>
#include <vector>

const size_t MAX_CHARS = 2048;
const int CHAR_WIDTH = 6;

class Text : public drawable
{
public:
	void draw( float x, float y, float angle );
	void printf( const char * fmt, ... );

private:
	std::vector<std::string> _stringQueue;

	void write_string( std::string str, float x, float y );

};
	

#endif // _TEXT_H_