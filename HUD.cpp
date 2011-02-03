/*
 *  HUD.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/30/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "HUD.h"
#include "button_defines.h"
#include "collision.h"

HUD::HUD() :
pPlayer(0)
{
	init();
}

HUD::HUD(game_sprite* pl) :
pPlayer(pl)
{
	init();
}

HUD::~HUD()
{
	
	attr = new spriteAttribute();
	ui_elements.clear();
	pPlayer = 0;
	delete pFPS;
	delete attr;
}

void HUD::init()
{
	frame = 0;
	time = 0;
	timebase = 0;
	pFPS = new spriteText(500, 50, 13, 6, 0, "FPS:" );
}

void HUD::draw()
{
	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	float fps = 0.0f;
	float frametime = 0.0f;
	
	if (time - timebase > 1000) {
		fps = frame*1000.0/(time-timebase);
		frametime = 1/fps;
	 	timebase = time;		
		frame = 0;
		pFPS->printf("FPS:%3.0f(%0.6f)", fps, frametime);
	}
	
	int i;
	for (i = 0; i < ui_elements.size(); i++)
	{
		ui_elements[i]->draw( 0.0f, 0.0f );
	}
	pFPS->draw(75,5);
}

void HUD::animate()
{
	int i;
	for (i = 0; i < ui_elements.size(); i++)
	{
		ui_elements[i]->animate();
	}
	pFPS->animate();
}

void HUD::includeElement(game_sprite* element)
{
	ui_elements.push_back(element);
}


int HUD::click(int state, int x, int y)
{
	int event = NO_EVENT;
	int i;
	for (i = 0; i < ui_elements.size(); i++)
	{
		if (inBox(x, y, ui_elements[i]->_x, ui_elements[i]->_y, ui_elements[i]->_x + ui_elements[i]->width, ui_elements[i]->_y + ui_elements[i]->height)) 
		{
			event = ui_elements[i]->click(state, x, y);
			if (event > NO_EVENT) {
				return event;
			}
		}
		ui_elements[i]->frame = 0;
	}
	return event;
}
