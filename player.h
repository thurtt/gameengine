/*
 *  player.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/23/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "sprite.h"


class Text;
class line_of_sight;
class game_sprite;

class Player : public game_sprite
{
public:
	Player( float _x_, float _y_, float _width_, float _height_, const char * _filename, std::vector<game_sprite*> * sprites );
	~Player();
	
private:
	line_of_sight * _los;
	Text * _text;
};

#endif // _PLAYER_H_