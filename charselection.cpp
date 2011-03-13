/*
 *  charselection.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 2/27/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "charselection.h"
#include "buttonsprite.h"
#include "playerselectsprite.h"


char_selection::char_selection()
{
	pPlayer = 0;
	selection_mask = 721;
	init();
	loadArchetypes();
	genElements();
}

char_selection::~char_selection()
{
	ui_elements.clear();
	pPlayer = 0;
	delete pFPS;
	delete attr;
}

void char_selection::loadArchetypes()
{
	/*get a list of available sets of player data.
	 I'm not 100% sure how to make this robust.*/
	
	//todo: load from file --
	
	//todo: load from database --
	
	
	archetypes.push_back(new player_data( "Blue Guy", "player_blue.png", point(0,0), point(32,32), 3));
	archetypes.push_back(new player_data( "Other Guy", "player_blue.png", point(0,0), point(32,32), 3));
}

void char_selection::genElements()
{
	int i;
	int x, y;
	
	for (i = 0; i < archetypes.size(); i++)
	{
		x = 10 + (i * 128);
		y = 10;
		includeElement( new player_select_sprite( x, y, 64, 64, archetypes[i]->texture, archetypes[i]->name, ( i + 1 ) * selection_mask) ); //use "i" return value to look up data.
	}
}

player_data * char_selection::selectedElement(int selection)
{
	int unmasked;
	unmasked = (selection - 1) / selection_mask;
	
	if ( unmasked <= archetypes.size() ) {
		return archetypes[unmasked];
	}
	else {
		return new player_data( "Bad selection", "default.png", point(0,0), point(0,0), 0 );
	}

}

