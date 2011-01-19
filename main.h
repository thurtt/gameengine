/*
 *  main.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/7/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "game.h"

#include <stdlib.h>
#include <vector>

#ifdef WIN32
#include <freeglut.h>
#elif defined(__APPLE__) || defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GLUT/glut.h>
#endif


void movementTimer(int value);
bool init();
