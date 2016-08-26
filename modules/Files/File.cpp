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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "File.hpp"

namespace hermod {
	namespace Files {

/**
 * @brief Default contructor
 *
 */
File::File()
{
	mName.clear();
	mPath.clear();
	mRoot = "/";
	mPermissivePath = false;
}

/**
 * @brief Add a new sub-directory to the relative path name
 *
 * @param path Name of the directory to add
 */
void File::addPath(const std::string &path)
{
	if (path.empty())
		return;
	
	if ( ! mPermissivePath)
	{
		if (path.at(0) == '.')
			return;
		if (path.at(0) == '\\')
			return;
	}
	mPath.append(path);
	mPath += '/';
}

std::string File::getFullname(void)
{
	std::string fullname;
	fullname += mRoot;
	fullname += mPath;
	fullname += mName;
	
	return fullname;
}

/**
 * @brief Get the name of the file
 *
 * @return string File name
 */
std::string File::getName(void)
{
	return mName;
}

/**
 * @brief Get the path where the file is located
 *
 * @return string Path name
 */
std::string File::getPath(void)
{
	return mPath;
}

/**
 * @brief Get the path used as "root" for file
 *
 * @return string Current path name used as root
 */
std::string File::getRoot(void)
{
	return mRoot;
}

/**
 * @brief Test if the file is a directory
 *
 * @return boolean True if the file is a directory
 */
bool File::isDirectory(void)
{
	std::string fullName;
	fullName =  mRoot;
	fullName += mPath;
	fullName += mName;
	
	struct stat fileStat;
	if (lstat(fullName.c_str(), &fileStat) == -1)
		return false; // ToDo : throw an error ?
	
	return S_ISDIR(fileStat.st_mode);
}

void File::setName(const std::string &name)
{
	mName = name;
}

void File::setPath(const std::string &path)
{
	mPath = path;
}

void File::setRoot(const std::string &root)
{
	if (root.empty())
	{
		mRoot = "/";
		return;
	}
	
	mRoot = root;
	
	// Add a final '/' to root path if needed
	if ('/' != root.at( root.length() - 1 ))
		mRoot += '/';
}

	} // namespace Files
} // namespace hermod
/* EOF */
