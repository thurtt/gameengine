/*
 *  main.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/7/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "main.h"
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

using namespace std;

game* baseGame;

void movementTimer(int value){
	baseGame->movement();
	glutTimerFunc(250/60, movementTimer, 1);
}

void animationTimer(int value){
	baseGame->animate();
	glutTimerFunc(1000/16, animationTimer, 1);
}

void fpsTimer(int value){
	
	glutPostRedisplay();
	
	glutTimerFunc(1000/60, fpsTimer, 1);
}

void display(void)
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	baseGame->draw();
	
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
	
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

void idle(void)
{
    //glutPostRedisplay();
}

/***********
 input
 **********/

void InputMovement(int key, int delta){
	if (delta == 0) {
		baseGame->focus_sprite->useAnimation(ANIM_NONE);
	}

	switch(key) {
		case GLUT_KEY_LEFT : 
			baseGame->focus_sprite->move_left = delta; break;
		case GLUT_KEY_RIGHT : 
			baseGame->focus_sprite->move_right = delta; break;
		case GLUT_KEY_UP : 
			baseGame->focus_sprite->move_up = delta; break;
		case GLUT_KEY_DOWN : 
			baseGame->focus_sprite->move_down = delta; break;
		default :
			break;
	}
}
void SpecialKeys(int key, int x, int y) {
	InputMovement(key, 1);
}

void SpecialKeysUp(int key, int x, int y) { 
	InputMovement(key, 0);
}

void NormalKeys(unsigned char key, int x, int y) {
	
	if (key == 27) {
		exit(0);
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
	if (key == '9'){
		glutGameModeString("640x480:32");
		if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)){
			glutEnterGameMode();
			init();
			baseGame->loadMap(1);
		}
	}
	if (key == '0'){
		glutLeaveGameMode();
		baseGame->loadMap(1);
	}
}
void NormalKeysUp(unsigned char key, int x, int y) {
	
	if (key == 27) {
		exit(0);
	}
	if (key == 'a'){
		InputMovement(GLUT_KEY_LEFT,0);
	}
	
	if (key == 'e'){
		baseGame->focus_sprite->useAnimation(ANIM_EXPLODE);;
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
}
void MouseActiveMotion(int x, int y) {
}
void MousePassiveMotion(int x, int y) {
}
void MainMouse(int button, int state, int x, int y) {
}
void MouseEntry(int state) {
}

void init(){
	glColor4f(1.0f,1.0f,1.0f,0.5f);			// Full Brightness, 50% Alpha ( NEW )
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
	
	glutKeyboardFunc(NormalKeys);
	glutKeyboardUpFunc(NormalKeysUp);
	glutSpecialFunc(SpecialKeys);
	glutSpecialUpFunc(SpecialKeysUp);
	glutMouseFunc(MainMouse);
	glutMotionFunc(MouseActiveMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutEntryFunc(MouseEntry);
	
	glutTimerFunc(1000/60,movementTimer,1);
	glutTimerFunc(900/60,fpsTimer,1);
	glutTimerFunc(1000/20,animationTimer,1);
	
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    
    glutCreateWindow("GLUT Program");
	
	baseGame = new game;
	init();
	
    
	/* ugh. */
	
		
    glutMainLoop();
    return EXIT_SUCCESS;
}