/*
 *  HUD.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/30/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */


#ifndef HUD_H
#define HUD_H

#include "sprite.h"
#include "player.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>


#include "spriteText.h"

class HUD {
	
private:
	vector<game_sprite *>  ui_elements;
	game_sprite* pPlayer; //player object to monitor for updates.
	int frame, time, timebase;
	int move, mtime, mtimebase;
	
public:
	spriteText * pFPS;
	spriteText * pMPS;
	spriteAttribute * attr;
	
	HUD();
	HUD(game_sprite* pl);
	~HUD();
	void init();
	void draw();
	void animate();
	void movement( float spriteTime );
	void includeElement(game_sprite* element);
	int click(int state, int x, int y);
};

#endif
