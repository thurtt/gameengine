/*
 *  main.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/7/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "main.h"
//#include <OpenAL/al.h>
//#include <OpenAL/alc.h>

using namespace std;

game* baseGame;

void movementTimer(int value){
	baseGame->movement();
	glutTimerFunc(1000/60, movementTimer, 1);
}

void animationTimer(int value){
	baseGame->animate();
	glutTimerFunc(1000/16, animationTimer, 1);
}

void fpsTimer(int value){
	
	glutPostRedisplay();
	
	glutTimerFunc(1000/75, fpsTimer, 1);
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

void SpecialKeys(int key, int x, int y) 
{
	baseGame->pInput->SpecialKeys(key, x, y);
}

void SpecialKeysUp(int key, int x, int y) 
{ 
	baseGame->pInput->SpecialKeysUp(key, x, y);
}

void NormalKeys(unsigned char key, int x, int y) 
{
	baseGame->pInput->NormalKeys(key, x, y);
}

void NormalKeysUp(unsigned char key, int x, int y) 
{	
	baseGame->pInput->NormalKeysUp(key, x, y);
}

void MouseActiveMotion(int x, int y) 
{
	baseGame->pInput->MouseActiveMotion(x, y);
}

void MousePassiveMotion(int x, int y) 
{
	baseGame->pInput->MousePassiveMotion(x, y);
}

void MainMouse(int button, int state, int x, int y) 
{
	baseGame->pInput->MainMouse(button, state, x, y);
}

void MouseEntry(int state) {
	baseGame->pInput->MouseEntry(state);
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
    glutInitWindowSize(1152, 648);
    
    glutCreateWindow("GLUT Program");
	
	baseGame = new game;
	init();
	
    
	/* ugh. */
	
		
    glutMainLoop();
    return EXIT_SUCCESS;
}