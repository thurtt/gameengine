/*
 *  map_manager.h
 *  gltest
 *
 *  Created by tom on 3/31/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include <string>
#include <vector>

const unsigned long MAX_FILENAME_LEN = 250;

#pragma pack(push,1)

struct SpriteObject
{
	float width;
	float height;
	float pos_x;
	float pos_y;
	unsigned long text_filename_len;
	char textFilename[MAX_FILENAME_LEN];
	// these are in pairs
	unsigned long attrib_count;
	unsigned long * attributes;
};


#pragma pack(pop)

enum FILE_OBJECT_TYPE
{
	TILE_FLOOR=0,
	SPRITE_WALL,
	SPRITE_PICKUP,
	SPRITE_GUARD,
	SPRITE_PLAYER
};



class FileLoader
{
public:
	void loadConfig( std::string filename );
	
	void saveConfig( std::string filename, const std::vector<SpriteObject> & config, bool newfile = false );
	
	std::vector<SpriteObject> getAllSpriteObjects();
	//std::vector<SpriteObject> getObjectsByType( FILE_OBJECT_TYPE type );
	
private:
	std::vector<SpriteObject> m_spriteObjects;
};

