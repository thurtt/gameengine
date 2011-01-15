/*
 *  input.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/8/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */
#ifndef INPUT_H
#define INPUT_H

class game_input {

public:
	game_input();
	void init();
	static void SpecialKeys(int key, int x, int y);
	static void NormalKeys(unsigned char key, int x, int y);
	static void MouseActiveMotion(int x, int y) ;
	static void MousePassiveMotion(int x, int y) ;
	static void MainMouse(int button, int state, int x, int y);
	static void MouseEntry(int state);
};
#endif