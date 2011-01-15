/*
 *  input.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/8/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "input.h"

#include <stdlib.h>
#include <GLUT/glut.h>
#include <string>

game_input::game_input(){
	init();
}

void game_input::init(){
	glutKeyboardFunc(NormalKeys);
	glutSpecialFunc(SpecialKeys);
	glutMouseFunc(MainMouse);
	glutMotionFunc(MouseActiveMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutEntryFunc(MouseEntry);
}

void game_input::SpecialKeys(int key, int x, int y) {
}

void game_input::NormalKeys(unsigned char key, int x, int y) {
	
	if (key == 27) {
		//exit(0);
	}
}
void game_input::MouseActiveMotion(int x, int y) {
}
void game_input::MousePassiveMotion(int x, int y) {
}
void game_input::MainMouse(int button, int state, int x, int y) {
}
void game_input::MouseEntry(int state) {
}