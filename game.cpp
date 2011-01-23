/*
 *  game.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/9/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "game.h"
#include "guard.h"
#include "player.h"
#include "los.h"

game::game(){
	frame = 0;
	timebase = 0;

	focus_sprite = new Player(102,700, 64,64, "player_blue.png", &sprites);
	sprites.push_back(focus_sprite);
	
	game_sprite * guard_sprite = new Guard( 202, 800, &sprites );
	sprites.push_back( guard_sprite );
	
	loadMap(1);
	
	_finished = false;
}

game::~game(){
	int i;
	for (i = 0; i < sprites.size(); i++){
		delete sprites[i];
	}
	for (i = 0; i < zones.size(); i++){
		delete zones[i];
	}
}

void game::draw(){
	int i;
	float toffx = offset_x;
	float toffy = offset_y;
	for (i = 0; i < zones.size(); i++){
		zones[i]->draw(toffx, toffy);
	}
	for (i = 0; i < sprites.size(); i++){
		sprites[i]->draw(toffx, toffy);
	}
}
void game::animate(){
	int i;
	float toffx = offset_x;
	float toffy = offset_y;
	for (i = 0; i < zones.size(); i++){
		zones[i]->animate(toffx, toffy);
	}
	for (i = 0; i < sprites.size(); i++){
		sprites[i]->animate();
	}
}

void game::movement(){
	int i;
	
	for (i = 0; i < sprites.size(); i++){
		sprites[i]->movement();
	}
	
	offset_x = (glutGet( GLUT_WINDOW_WIDTH ) - focus_sprite->width) / 2 - focus_sprite->_x;
	offset_y = (glutGet( GLUT_WINDOW_HEIGHT )  - focus_sprite->height) / 2 - focus_sprite->_y;
}

bool game::finished(){ return _finished; }
bool game::finished(bool fin){ _finished = fin; return _finished; }

void game::genTiles(){
	populateTileSet();
}

void game::loadMap(int map){
	// map is series of zones
	zones.clear();
	genTiles();
	
	int i;
	for ( i = 0; i < 16; i++){
		zones.push_back( new zone( i ) );
	}
}

void game::idle(){
	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	
}

