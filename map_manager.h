/*
 *  map_manager.h
 *  gltest
 *
 *  Created by tom on 3/31/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#pragma pack(push,1)

struct SpriteObject
{
	unsigned long type;
	float width;
	float height;
	float pos_x;
	float pos_y;
	char * img_file;
	unsigned long file_len;
};

struct TileObject
{
	unsigned long type;
	float width;
	float height;
	float pos_x;
	float pos_y;
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
private:
};