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

class HUD {
	
private:
	map<int, int> _attributes;
	vector<game_sprite *>  ui_elements;
	game_sprite* pPlayer; //player object to monitor for updates.
	
public:
	HUD();
	HUD(game_sprite* pl);
	~HUD();
	void draw();
	void animate();
	void includeElement(game_sprite* element);
	void setAttribute(int _attr, int val);
	int getAttribute(int _attr);
	int click(int state, int x, int y);
};

#endif
