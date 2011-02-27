/*
 *  charselection.h
 *  gltest
 *
 *  Created by Stuart Templeton on 2/27/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#ifndef CHARSELECTION_H
#define CHARSELECTION_H

#include "HUD.h"
#include "player_data.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>


class char_selection : public HUD {
private:
	
public:
	char_selection();
	~char_selection();
	
	void loadArchetypes(); // this will load huge qty of player_data
	void genElements(); //generate ui elements for each of player_data
	player_data * selectedElement(int selection);
	vector<player_data *>  archetypes;
	
	int selection_mask;
	
};

#endif // CHARSELECTION_H