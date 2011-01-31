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
	
}

HUD::HUD(game_sprite* pl) :
pPlayer(pl)
{
}

HUD::~HUD()
{
	ui_elements.clear();
	pPlayer = 0;
}

void HUD::draw()
{
	int i;
	for (i = 0; i < ui_elements.size(); i++)
	{
		ui_elements[i]->draw( 0.0f, 0.0f );
	}
}

void HUD::animate()
{
	int i;
	for (i = 0; i < ui_elements.size(); i++)
	{
		ui_elements[i]->animate();
	}
}

void HUD::includeElement(game_sprite* element)
{
	ui_elements.push_back(element);
}

void HUD::setAttribute(int _attr, int _val)
{
	_attributes[_attr] = _val;
}

int HUD::getAttribute(int _attr)
{
	if (_attributes.find(_attr) != _attributes.end() )
	{
		return _attributes[_attr];
	}
	return 0;
}

int HUD::click(int state, int x, int y)
{
	int event = NO_EVENT;
	int i;
	for (i = 0; i < ui_elements.size(); i++)
	{
		if (inBox(x, y, ui_elements[i]->_x, ui_elements[i]->_y, ui_elements[i]->_x + ui_elements[i]->width, ui_elements[i]->_y + ui_elements[i]->height)) 
		{
			event = ui_elements[i]->getAttribute(BUTTON_RETURN_VALUE);
			if (event > NO_EVENT) {
				return event;
			}
		}
	}
	return event;
}
