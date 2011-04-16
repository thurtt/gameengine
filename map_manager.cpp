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
#include <assert.h>

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
	unsigned long blocksRead = 0;
	const unsigned long objHeadSize = ( sizeof( SpriteObject ) - ( ( MAX_FILENAME_LEN - 1 ) + sizeof( unsigned long ) + sizeof( unsigned long * ) ) );
	
	// old school trick to get the file size
	fseek( hFile, 0, SEEK_END );
	bytesInFile = ftell( hFile ); // 0 based
	fseek( hFile, 0, SEEK_SET );
	

	
	while ( ( totalBytesRead < bytesInFile ) && !feof( hFile ) )
	{
		
		SpriteObject loadObj;
		memset( &loadObj, 0, sizeof(SpriteObject) );
		
		// only read up to the filename since it can be variable length
		blocksRead = fread( &loadObj, sizeof( unsigned char ), objHeadSize , hFile );
		assert( blocksRead == objHeadSize );
		totalBytesRead += blocksRead;
		
		// now take the filename len to determine how much filename we need to read in
		unsigned long readLen = loadObj.text_filename_len;
		if ( readLen > MAX_FILENAME_LEN )
		{
			readLen = MAX_FILENAME_LEN;
		}
		blocksRead = fread( loadObj.textFilename, sizeof( unsigned char ), readLen, hFile );
		assert( blocksRead == loadObj.text_filename_len );
		totalBytesRead += blocksRead;
		
		// read in the size of our attributes
		blocksRead = fread( &( loadObj.attrib_count ), sizeof( unsigned long ), 1, hFile );
		assert( blocksRead == 1 );
		totalBytesRead += ( blocksRead * sizeof( unsigned long ) );
		
		// load up the attributes
		loadObj.attributes = new unsigned long[loadObj.attrib_count];
		blocksRead = fread( loadObj.attributes, sizeof( unsigned long ), loadObj.attrib_count, hFile );
		assert( blocksRead == loadObj.attrib_count );
		totalBytesRead += ( blocksRead * sizeof( unsigned long ) );
		
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
		unsigned long bytesToWrite = ( sizeof( SpriteObject ) - ( ( MAX_FILENAME_LEN - 1 ) + sizeof( unsigned long ) + sizeof( unsigned long * ) ) );
		
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
