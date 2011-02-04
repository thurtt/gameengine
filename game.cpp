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
#include "buttonsprite.h"
#include "los.h"
#include "game_states.h"
#include "button_defines.h"
#include "textAttributeReport.h"

#ifdef WIN32
	#include <windows.h>
#endif

game::game(){
	
	attr = new spriteAttribute();
	
	attr->setAttribute(GAME_PAUSED, 0);
	attr->setAttribute(GAME_PHASE, 0);
	frame = 0;
	timebase = 0;
	focus_sprite = 0;
	pHUD = 0;
	pMap = new game_map();
	pInput = new game_input( this );
	
	loadPhase(STATE_TITLE);
	
	_finished = false;
}

game::~game(){
	int i;
	for (i = 0; i < sprites.size(); i++){
		delete sprites[i];
	}
	delete pMap;
	delete pHUD;
	delete pInput;
	delete attr;
}

void game::draw(){
	int i;
	float toffx = offset_x;
	float toffy = offset_y;
	
	pMap->draw(toffx, toffy);
	
	for (i = 0; i < sprites.size(); i++){
		sprites[i]->draw(toffx, toffy);
	}
	
	if (pHUD != 0)
		pHUD->draw();
}
void game::animate(){
	int i;
	float toffx = offset_x;
	float toffy = offset_y;
	
	pMap->animate(toffx, toffy);
	
	for (i = 0; i < sprites.size(); i++){
		sprites[i]->animate();
	}
	
	if (pHUD != 0)
		pHUD->animate();
}

void game::movement(){

#ifdef WIN32
	LARGE_INTEGER ticksPerSecond;
	LARGE_INTEGER startTick, stopTick;   // A point in time 
	QueryPerformanceFrequency(&ticksPerSecond);
	QueryPerformanceCounter(&startTick);
#endif
	if (attr->getAttribute(GAME_PAUSED) > 0)
		return;
	
	float spriteTime;
	int i;
	
	for (i = 0; i < sprites.size(); i++){

		sprites[i]->movement();
	}

	if (focus_sprite != 0){ //if we have something to follow....
		offset_x = (glutGet( GLUT_WINDOW_WIDTH ) - focus_sprite->width) / 2 - focus_sprite->_x;
		offset_y = (glutGet( GLUT_WINDOW_HEIGHT )  - focus_sprite->height) / 2 - focus_sprite->_y;
	}
#ifdef WIN32
		QueryPerformanceCounter(&stopTick);
		spriteTime = ( stopTick.QuadPart - startTick.QuadPart ) / ( ticksPerSecond.QuadPart * 1.0f );
#endif

	if (pHUD != 0)
		pHUD->movement( spriteTime );
}

bool game::finished(){ return _finished; }
bool game::finished(bool fin){ _finished = fin; return _finished; }

void game::loadPhase(int phase){
	
	attr->setAttribute(GAME_PHASE, phase);
	
	
	switch (phase) {
		case STATE_TITLE:
			midPhase(); //a little clean-up here.
			pHUD = new HUD();
			pHUD->includeElement( new game_sprite(0,0, glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ), "title_screen.png", false, false) );
			pHUD->includeElement( new button_sprite( (glutGet( GLUT_WINDOW_WIDTH ) /2 ) - (415 / 2),120,128,415,"start_button.png", STATE_LEVEL_STARTING) );
			break;
		case STATE_LEVEL_STARTING:
			midPhase();
			loadMap(1);
			if (pHUD != 0)
			{
				delete pHUD;
				pHUD = 0;
			}
			pHUD = new HUD(focus_sprite);
			pHUD->includeElement( new button_sprite( (glutGet( GLUT_WINDOW_WIDTH ) /2 ) - (415 / 2),120,128,415,"start_button.png", START_GAME) );
			
			break;
		case STATE_LEVEL:
			if (pHUD != 0)
			{
				delete pHUD;
				pHUD = 0;
			}
			pHUD = new HUD(focus_sprite);
			pHUD->includeElement(new textAttributeReport(5,5, focus_sprite, PICKUP_SCORE, "Score: %d"));
			pHUD->includeElement( new button_sprite( glutGet( GLUT_WINDOW_WIDTH )  - 64 - 10,glutGet( GLUT_WINDOW_HEIGHT )  - 64 - 10,64,64,"pause_button.png", PAUSE_GAME) );
			
			attr->setAttribute(GAME_PAUSED, 0);
			break;
		case STATE_LEVEL_FINISHED:
			midPhase();
			break;
		default:
			break;
	}
}

void game::loadMap(int _map){

	//
	//first order of business, make the game not run. This is the "loading screen"
	//
	attr->setAttribute(GAME_PAUSED, 1);
	
	//
	//Generate the map
	//
	pMap->loadMap(_map);
	
	//
	//Populate the pickups
	//
	game_sprite * pu = new game_sprite(120,780, 16,16, "pickup_thing.png", 0, 0);
	pu->includeAnimation(ANIM_EXPLODE, "explosion.png", 25);
	game_sprite * pu2 = new game_sprite(150,780, 16,16, "pickup_thing.png", 0, 0);
	pu2->includeAnimation(ANIM_EXPLODE, "explosion.png", 25);
	game_sprite * pu3 = new game_sprite(220,780, 32,32, "pickup_thing.png", 0, 0);
	pu3->includeAnimation(ANIM_EXPLODE, "explosion.png", 25);
	
	sprites.push_back( pu );
	sprites.push_back( pu2 );
	sprites.push_back( pu3 );
	
	pickups.push_back( pu );
	pickups.push_back( pu2 );
	pickups.push_back( pu3 );
	
	//
	//create the player
	//
	focus_sprite = new Player(102,700, 32,32, "player_blue.png", &sprites, &pickups, pMap);
	sprites.push_back(focus_sprite);
	players.push_back(focus_sprite);
	
	//
	// and some guards
	//
	Guard * guard_sprite = new Guard( 202, 800, &players, pMap );
	sprites.push_back( guard_sprite );

}

void game::midPhase(){
	pMap->clearMap();
	sprites.clear();
	if (pHUD != 0)
	{
		delete pHUD;
		pHUD = 0;
	}
}

void game::idle(){
	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	
}

