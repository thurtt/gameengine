/*
 *  spriteAttribute.h
 *  gltest
 *
 *  Created by Stuart Templeton on 2/2/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#ifndef SPRITEATTRIBUTE_H
#define SPRITEATTRIBUTE_H

#include <map>

using namespace std;

class spriteAttribute {
	
public:
	map<int, int> _attributes;
	spriteAttribute();
	~spriteAttribute();	
	void setAttribute( int _attr, int val);
	int getAttribute( int _attr);
};

#endif // SPRITEATTRIBUTE_H