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

struct FileObject
{
	unsigned long type;
	float width;
	float height;
	float pos_x;
	float pos_y;
	unsigned long img_filename_len;
	char img_filename[MAX_FILENAME_LEN + 1];	
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
	
	void saveConfig( std::string filename, const std::vector<FileObject> & config );
	
	std::vector<FileObject> getAllFileObjects();
	std::vector<FileObject> getObjectsByType( FILE_OBJECT_TYPE type );
	
private:
	std::vector<FileObject> m_fileObjects;
};

