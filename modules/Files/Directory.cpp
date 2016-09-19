/*
 * modFiles - An Hermod module to access static files
 *
 * Copyright (c) 2016 Cowlab
 *
 * Hermod is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License 
 * version 3 as published by the Free Software Foundation. You
 * should have received a copy of the GNU Lesser General Public
 * License along with this program, see LICENSE file for more details.
 * This program is distributed WITHOUT ANY WARRANTY see README file.
 *
 * Authors: Saint-Genest Gwenael <gwen@hooligan0.net>
 */
#include <iostream>
#include <dirent.h>
#include "Directory.hpp"

namespace hermod {
	namespace Files {

/**
 * @brief Default constructor
 *
 */
Directory::Directory()
  : File()
{
	mFiles.clear();
	mValidList = false;
}

/**
 * @brief Constructor that initialize object from a File
 *
 * @param source The file used as model
 */
Directory::Directory(File &source)
  : File()
{
	mFiles.clear();
	mValidList = false;
	
	setRoot( source.getRoot() );
	setPath( source.getPath() );
	setName( source.getName() );
}

/**
 * @brief Default destructor
 *
 */
Directory::~Directory()
{
	// Clear the files listing
	clear();
}

/**
 * @brief Get one file entry listed into this directory
 *
 * @param index An integer of the file index into the cache
 * @return File* Pointer to the File entry
 */
File *Directory::at(int index)
{
	// If the current cache is invalid
	if ( ! mValidList)
		// Refresh the cache content
		refresh();
	
	// If the requested index is above the number of items into the cache
	if (index >= mFiles.size())
		// Then, return NULL entry
		return NULL;
	
	// Return the 'index' entry from current cache
	return mFiles.at(index);
}

/**
 * @brief Clear the file listing cache
 *
 */
void Directory::clear(void)
{
	while( mFiles.size() )
	{
		File *f = mFiles.back();
		mFiles.pop_back();
		delete f;
	}
	mValidList = false;
}

/**
 * @brief Get the number of entries into the directory
 *
 * @return integer Number of items found into the directory
 */
int Directory::count(void)
{
	// If the current cache is invalid
	if ( ! mValidList)
		// Refresh the cache content
		refresh();
	
	// Return the number of entries into the cache
	return mFiles.size();
}

/**
 * @brief Load (or reload) the listing of entries into directory
 *
 */
void Directory::refresh(void)
{
	// Clear the current cache
	clear();
	
	DIR *pdir;
	struct dirent *pent;
	
	// Use system to "open" the directory
	pdir = opendir( getFullname().c_str() );
	if ( ! pdir)
		return;
	// Read all entries from directory
	while ((pent=readdir(pdir)))
	{
		std::string entryName(pent->d_name);
		// Ignore "." and ".." entries
		if (entryName.compare(".") == 0)
			continue;
		if (entryName.compare("..") == 0)
			continue;
		// Create a new entry into the cache
		File *newFile = new File();
		newFile->setRoot( getRoot() );
		newFile->setPath( getPath() );
		newFile->addPath( getName() );
		newFile->setName( std::string(pent->d_name) );
		mFiles.push_back(newFile);
	}
	// Inform system that we "close" the directory
	closedir(pdir);
	
	// Values into the cache are now up-to-date
	mValidList = true;
}

	} // namespace Files
} // namespace hermod
/* EOF */
