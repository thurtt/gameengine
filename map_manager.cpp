/*
 *  map_manager.cpp
 *  gltest
 *
 *  Created by tom on 3/31/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdexcept>
#include "map_manager.h"

void FileLoader::loadConfig( std::string filename )
{
	FILE * hFile = fopen( filename.c_str(), "rb" );
	if ( hFile == 0 )
	{
		/// bye bye
		throw std::runtime_error( "Cannot open configuration file" );
	}
	
	unsigned long bytesInFile = 0;
	unsigned long totalBytesRead = 0;
	
	// old school trick to get the file size
	fseek( hFile, 0, SEEK_END );
	bytesInFile = ftell( hFile ) + 1; // 0 based
	fseek( hFile, 0, SEEK_SET );
	
	while ( totalBytesRead < bytesInFile )
	{
		
		SpriteObject loadObj;
		memset( &loadObj, 0, sizeof(SpriteObject) );
		
		// only read up to the filename since it can be variable length
		totalBytesRead += fread( &loadObj, sizeof( unsigned char ), ( sizeof( SpriteObject ) - MAX_FILENAME_LEN + 1 ), hFile );
		
		// now take the filename len to determine how much filename we need to read in
		unsigned long readLen = loadObj.text_filename_len;
		if ( readLen > MAX_FILENAME_LEN )
		{
			readLen = MAX_FILENAME_LEN;
		}
		totalBytesRead = fread( loadObj.textFilename, sizeof( unsigned char ), readLen, hFile );
		
		// add it to our list
		m_spriteObjects.push_back( loadObj );
		
	}
	
	fclose( hFile );
}
	
void FileLoader::saveConfig( std::string filename, const std::vector<SpriteObject> & config, bool newfile )
{
	
	FILE * hFile = 0;
	
	if ( newfile )
	{
		hFile = fopen( filename.c_str(), "wb" );
	}
	else 
	{
		hFile = fopen( filename.c_str(), "ab" );
	}

	if ( hFile == 0 )
	{
		/// bye bye
		throw std::runtime_error( "Cannot open configuration file" );
	}
	
	
	for ( int i = 0; i < config.size(); i++ )
	{
		unsigned long bytesToWrite = ( sizeof( SpriteObject ) - ( ( MAX_FILENAME_LEN - 1 ) + ( sizeof( unsigned long ) + ( sizeof( unsigned long ) * config[i].attrib_count ) ) ) );
		
		// write out the main object
		fwrite( &(config[i]), sizeof( unsigned char ), bytesToWrite, hFile );
		
		// write out the filename
		fwrite( config[i].textFilename, sizeof( unsigned char ), config[i].text_filename_len, hFile );
		
		// write out any attributes. We need to write out the attribute count regardless of whether or not any exist
		fwrite( &(config[i].attrib_count), sizeof( unsigned long ), 1, hFile );
		
		// We can directly write out the entire attributes array in one line...badass
		fwrite( config[i].attributes, sizeof( unsigned long ), config[i].attrib_count, hFile ); 
	}
	
	fclose( hFile );
}
	
std::vector<SpriteObject> FileLoader::getAllSpriteObjects()
{
	return m_spriteObjects;
}

/*std::vector<FileObject> FileLoader::getObjectsByType( FILE_OBJECT_TYPE type )
{
	std::vector<FileObject> tmpResult;
	std::vector<FileObject>::iterator itr = m_fileObjects.begin();
	
	while( itr != m_fileObjects.end() )
	{
		if ( itr->type == type )
		{
			tmpResult.push_back( *itr );
		}
		++itr;
	}
	return tmpResult;
}*/
	
