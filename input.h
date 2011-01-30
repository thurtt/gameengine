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


class game;

class game_input {
private:
	game * pGame;

public:
	game_input(game * _pGame);
	~game_input();
	void init();
	void InputMovement(int key, int delta);
	void SpecialKeys(int key, int x, int y);
	void SpecialKeysUp(int key, int x, int y);
	void NormalKeys(unsigned char key, int x, int y);
	void NormalKeysUp(unsigned char key, int x, int y);
	void MouseActiveMotion(int x, int y) ;
	void MousePassiveMotion(int x, int y) ;
	void MainMouse(int button, int state, int x, int y);
	void MouseEntry(int state);
};
#endif