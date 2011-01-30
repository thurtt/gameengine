/*
 *  HUD.h
 *  gltest
 *
 *  Created by Stuart Templeton on 1/30/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

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
	Player* pPlayer; //player object to monitor for updates.
	
public:
	HUD(Player* pl);
	~HUD();
	void draw();
	void animate();
	void setAttribute(int _attr, int val);
	int getAttribute(int _attr);
};