#include "text.h"
#include <cstdio>
#include <cstdarg>

#ifdef WIN32
#include <freeglut.h>
#elif defined(__APPLE__) || defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GLUT/glut.h>
#endif

Text::Text() :
_msg(0)
{
	_msg = new char[MAX_CHARS];
}

Text::~Text()
{
	delete [] _msg;
}

void Text::printf( const char * format, ... )
{
	va_list va_args;
	
	va_start( va_args, format );

	vsnprintf( _msg, MAX_CHARS, format, va_args );
	_msg[MAX_CHARS-1] = '\0';
}

void Text::draw( float x, float y, float angle )
{
	glDisable(GL_DEPTH_TEST);
	
	for( int i = 0; i < MAX_CHARS; i++ )
	{
		if ( _msg[i] == '\0' )
		{
			break;
		}
		
		glRasterPos2f( x, y );
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, _msg[i] );
		x += CHAR_WIDTH;
	}
	glEnable(GL_DEPTH_TEST);
	_msg[0] = '\0';
}