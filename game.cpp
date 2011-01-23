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
#include "game_states.h"

game::game(){
	frame = 0;
	timebase = 0;
	focus_sprite = 0;
	_phase = 0;

	loadPhase(STATE_TITLE);
	
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
	if (focus_sprite != 0){ //if we have something to follow....
		offset_x = (glutGet( GLUT_WINDOW_WIDTH ) - focus_sprite->width) / 2 - focus_sprite->_x;
		offset_y = (glutGet( GLUT_WINDOW_HEIGHT )  - focus_sprite->height) / 2 - focus_sprite->_y;
	}
}

bool game::finished(){ return _finished; }
bool game::finished(bool fin){ _finished = fin; return _finished; }

void game::genTiles(){
	populateTileSet();
}

void game::loadPhase(int phase){
	
	_phase = phase;
	
	
	switch (phase) {
		case STATE_TITLE:
			midPhase(); //a little clean-up here.
			sprites.push_back( new game_sprite(0,0, glutGet( GLUT_WINDOW_WIDTH ),glutGet( GLUT_WINDOW_HEIGHT ), "title_screen.png", false, false) );
			
			break;
		case STATE_LEVEL_STARTING:
			midPhase();
			loadMap(1);
			break;
		case STATE_LEVEL:
			break;
		case STATE_LEVEL_FINISHED:
			midPhase();
			break;
		default:
			break;
	}
}

void game::loadMap(int map){
	// map is series of zones
	genTiles();
	
	int i;
	for ( i = 0; i < 16; i++){
		zones.push_back( new zone( i ) );
	}
	sprites.push_back( new game_sprite(120,780, 16,16, "pickup_thing.png", false, false) );
	sprites.push_back( new game_sprite(150,780, 32,32, "pickup_thing.png", false, false) );
	sprites.push_back( new game_sprite(220,780, 64,64, "pickup_thing.png", false, false) );
	
	
	focus_sprite = new Player(102,700, 64,64, "player_blue.png", &sprites);
	sprites.push_back(focus_sprite);
	
	game_sprite * guard_sprite = new Guard( 202, 800, &sprites );
	sprites.push_back( guard_sprite );

	
}

void game::midPhase(){
	zones.clear();
	sprites.clear();
}

void game::idle(){
	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	
}

