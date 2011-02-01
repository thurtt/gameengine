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
		if ( pGame->_phase == 0){
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
		vector<tile*> pTiles;
		pTiles = pGame->pMap->getTiles(pGame->focus_sprite->_x,pGame->focus_sprite->_y,pGame->focus_sprite->height,pGame->focus_sprite->width);
		sz = pTiles.size();
		
		int i;
		int k;
		for (i = 0; i < pTiles.size(); i++){
			for (k = 0; k < pTiles[i]->sprites.size(); k++){
				pTiles[i]->sprites[k]->active = false;
			}
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
	iReturn = pGame->pHUD->click(state,x, glutGet( GLUT_WINDOW_HEIGHT ) - y);
	if (iReturn == NO_EVENT) {
		//interract with the world
	}
	else {
		//do something based on phase
		switch (iReturn) {
			case EVENT_ACCEPTED:
				//dump
				break;
			case START_GAME:
				//YOU HEAR THE MAN!
				pGame->loadPhase(STATE_LEVEL_STARTING);
				break;

			default:
				break;
		}
	}

}

void game_input::MouseEntry(int state) 
{
}
