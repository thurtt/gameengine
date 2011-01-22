#include "text.h"
#include <cstdio>

#ifdef WIN32
#include <freeglut.h>
#elif defined(__APPLE__) || defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GLUT/glut.h>
#endif

void Text::printf( const char * format, ... )
{
	va_list va_args;
	char * buffer = new char[MAX_CHARS];

	va_start( va_args, format );

	vsnprintf( buffer, MAX_CHARS, format, va_args );
	std::string tempStr = buffer;

	delete [] buffer;

	_stringQueue.push_back( tempStr );
}

void Text::draw( float x, float y, float angle )
{
	for( int i = 0; i < _stringQueue.size(); i++ )
	{
		write_string( _stringQueue[i], x, y );
	}
}

void Text::write_string( std::string str, float x, float y )
{
	for( int i = 0; i < str.length(); i++ )
	{
		glRasterPos2f( x, y );
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, str[i] );
		x += CHAR_WIDTH;
	}
}