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
		
		FileObject loadObj;
		memset( &loadObj, 0, sizeof(FileObject) );
		
		// only read up to the filename since it can be variable length
		totalBytesRead += fread( &loadObj, sizeof( unsigned char ), ( sizeof( FileObject ) - MAX_FILENAME_LEN + 1 ), hFile );
		
		// now take the filename len to determine how much filename we need to read in
		unsigned long readLen = loadObj.img_filename_len;
		if ( readLen > MAX_FILENAME_LEN )
		{
			readLen = MAX_FILENAME_LEN;
		}
		totalBytesRead = fread( loadObj.img_filename, sizeof( unsigned char ), readLen, hFile );
		
		// add it to our list
		m_fileObjects.push_back( loadObj );
		
	}
	
	fclose( hFile );
}
	
void FileLoader::saveConfig( std::string filename, const std::vector<FileObject> & config )
{
	FILE * hFile = fopen( filename.c_str(), "wb" );
	if ( hFile == 0 )
	{
		/// bye bye
		throw std::runtime_error( "Cannot open configuration file" );
	}
	
	// save things to the end of the file
	fseek( hFile, 0, SEEK_END );
	
	for ( int i = 0; i < config.size(); i++ )
	{
		// write out the main object
		fwrite( &(config[i]), sizeof( unsigned char ), ( sizeof( FileObject ) - ( MAX_FILENAME_LEN - 1 ) ) , hFile );
		
		// write out the filename
		fwrite( config[i].img_filename, sizeof( unsigned char ), config[i].img_filename_len, hFile );

	}
	
	fclose( hFile );
}
	
std::vector<FileObject> FileLoader::getAllFileObjects()
{
	return m_fileObjects;
}

std::vector<FileObject> FileLoader::getObjectsByType( FILE_OBJECT_TYPE type )
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
}
	
