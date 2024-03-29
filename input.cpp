/*
 *  input.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/8/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "input.h"
#include "game.h"
#include "button_defines.h"
#include "game_states.h"
#include "line.h"
#include "player.h"
#include "player_data.h"

#include <stdlib.h>
#include <string>

#ifdef WIN32
	#include <freeglut.h>
#elif defined(__APPLE__) || defined(__APPLE_CC__)
	#include <GLUT/glut.h>
#else
	#include <GLUT/glut.h>
#endif


game_input::game_input(game * _pGame) :
pGame(_pGame)
{
	//init();
}

game_input::~game_input()
{
}

void game_input::init()
{
	/*glutKeyboardFunc(NormalKeys);
	glutSpecialFunc(SpecialKeys);
	glutMouseFunc(MainMouse);
	glutMotionFunc(MouseActiveMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutEntryFunc(MouseEntry);*/
}

void game_input::InputMovement(int key, int delta)
{
	if (delta == 0) {
		pGame->focus_sprite->useAnimation(ANIM_NONE);
	}
	
	switch(key) {
		case GLUT_KEY_LEFT : 
			pGame->focus_sprite->move_left = delta; break;
		case GLUT_KEY_RIGHT : 
			pGame->focus_sprite->move_right = delta; break;
		case GLUT_KEY_UP : 
			pGame->focus_sprite->move_up = delta; break;
		case GLUT_KEY_DOWN : 
			pGame->focus_sprite->move_down = delta; break;
		default :
			break;
	}
}

void game_input::SpecialKeys(int key, int x, int y) 
{
	InputMovement(key, 1);
}

void game_input::SpecialKeysUp(int key, int x, int y) 
{
	InputMovement(key, 0);
}

void game_input::NormalKeys(unsigned char key, int x, int y) {
	
	if (key == 27) {
		exit(0);
	}
	if (key == 13) {
		if ( pGame->attr->getAttribute(GAME_PHASE) == 0){
			pGame->loadPhase(3);
		}
	}
	if (key == 'a'){
		InputMovement(GLUT_KEY_LEFT,1);
	}
	if (key == 'd'){
		InputMovement(GLUT_KEY_RIGHT,1);
	}
	if (key == 's'){
		InputMovement(GLUT_KEY_DOWN,1);
	}
	if (key == 'w'){
		InputMovement(GLUT_KEY_UP,1);
	}
	/* TEMPORARY REMOVAL: init() doesn't work properly yet. scoping. */
	/*
	if (key == '9'){
		glutGameModeString("1152x648:32");
		if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)){
			glutEnterGameMode();
			init();
			pGame->loadMap(1);
		}
	}
	if (key == '0'){
		glutLeaveGameMode();
		pGame->loadMap(1);
	}
	 */
	
}

void game_input::NormalKeysUp(unsigned char key, int x, int y)
{
	int sz;
	if (key == 27) {
		exit(0);
	}
	if (key == 'a'){
		InputMovement(GLUT_KEY_LEFT,0);
	}
	
	if (key == 'e'){
		pGame->focus_sprite->useAnimation(ANIM_EXPLODE);;
	}
	
	if (key == 't'){
		tile* pTile;
		pTile = pGame->pMap->getTile(pGame->focus_sprite->_x,pGame->focus_sprite->_y);
		
		int k;
			for (k = 0; k < pTile->sprites.size(); k++){
				pTile->sprites[k]->active = false;
			}
	}
	if (key == 'd'){
		InputMovement(GLUT_KEY_RIGHT,0);
	}
	if (key == 's'){
		InputMovement(GLUT_KEY_DOWN,0);
	}
	if (key == 'w'){
		InputMovement(GLUT_KEY_UP,0);
	}
	if (key == '8'){
		pGame->pHUD->pFPS->active = pGame->pHUD->pFPS->active ? false : true;
		pGame->pHUD->pMPS->active = pGame->pHUD->pMPS->active ? false : true;
	}
	if ( key == 'f' ){
		pGame->saveMap();
	}
	
}

void game_input::MouseActiveMotion(int x, int y) 
{
}

void game_input::MousePassiveMotion(int x, int y) 
{
}

void game_input::MainMouse(int button, int state, int x, int y) 
{
	//check hud for response
	int iReturn;
	float adj_y = glutGet( GLUT_WINDOW_HEIGHT ) - y;
	iReturn = pGame->pHUD->click(state,x, adj_y );
	if (iReturn == NO_EVENT) {
		//interract with the world
		
		// Set a waypoint for the player
		if (pGame->players.size() > 0){
			Player * pPlayer = dynamic_cast<Player *>( pGame->players[0] );
			pPlayer->_wpmgr.addWaypoint( pPlayer->dispToWorld( x, adj_y ) );
			pGame->pMap->PlaceMarker( pPlayer->dispToWorld( x, adj_y ) );
			
		}
	}
	else if (iReturn != EVENT_ACCEPTED) {
		//case is game phase, if/then iReturn value.
		
		switch ( pGame->attr->getAttribute(GAME_PHASE) ) {
			case STATE_TITLE:
				// do eet.
				if (iReturn == STATE_CHARACTER_SELECT) {
					//Ou est la pamplemousse? DANS LA SALLE DE BAINS!
					pGame->loadPhase(STATE_CHARACTER_SELECT);
				}
				break;
				
			case STATE_CHARACTER_SELECT:
				if (iReturn == STATE_TITLE) {
					//touchy touchy
					pGame->loadPhase(STATE_TITLE);
				}
				else {
					//get player data selected
					//YOU HEAR THE MAN!
					pGame->player_configuration = dynamic_cast<char_selection *>( pGame->pHUD )->selectedElement(iReturn);
					pGame->loadPhase(STATE_LEVEL_STARTING);
				}

				break;
			case STATE_LEVEL_STARTING:
				if (iReturn == START_GAME) {
					//cry havok
					pGame->loadPhase(STATE_LEVEL);
				}
				break;
			case STATE_LEVEL:
				if (iReturn == PAUSE_GAME) {
					//put it on hold
					if (pGame->attr->getAttribute(GAME_PAUSED) > 0){
						pGame->attr->setAttribute(GAME_PAUSED, 0);}
					else {
						pGame->attr->setAttribute(GAME_PAUSED, 1);
					}
				}
				break;
			default:
				break;
		}
	}

}

void game_input::MouseEntry(int state) 
{
}
