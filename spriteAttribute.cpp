/*
 *  spriteAttribute.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 2/2/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "spriteAttribute.h"

spriteAttribute::spriteAttribute()
{
}

spriteAttribute::~spriteAttribute()
{
	_attributes.clear();
}


void spriteAttribute::setAttribute(int _attr, int _val){
	_attributes[_attr] = _val;
}

int spriteAttribute::getAttribute(int _attr){
	if (_attributes.find(_attr) != _attributes.end() )
	{
		return _attributes[_attr];
	}
	return 0;
}