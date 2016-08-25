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
#include <fstream>
#include <string>
#include "PageFile.hpp"
#include "Config.hpp"

PageFile::PageFile(void)
    : Page()
{
	// Nothing to do
}

int PageFile::process(void)
{
	Config  *cfg = Config::getInstance();
	// Get the root path for files
	std::string fileRoot = cfg->get("mod:Files", "root");
	if (fileRoot.empty())
		throw runtime_error("Missing config (root)");
	
	// If the request have no argument, filename is missing
	if (getArgCount() == 0)
		return(-1);
	
	// Add a final '/' to root path if needed
	if ('/' != fileRoot.at( fileRoot.length() - 1 ))
		fileRoot += '/';
	
	// Compute relative (sub-)path of the file
	std::string pathName;
	for (int i = 1; i < getArgCount(); i++)
	{
		std::string arg = getArg(i);
		// Exclude all names starting with '.' (mainly for "..")
		if (arg.at(0) == '.')
			continue;
		if (arg.at(0) == '\\')
			continue;
		// Add this argument to the pathname
		pathName.append(arg);
		pathName += '/';
	}
	
	// Get the file name (last argument)
	std::string fileName = getArg( getArgCount() );
	
	
	std::string fullName;
	fullName = fileRoot;
	if ( ! pathName.empty() )
		fullName += pathName;
	fullName += fileName;
	
	// Open file
	std::fstream dataFile;
	dataFile.open(fullName.c_str(), std::ios::in|std::ios::binary);
	if ( ! dataFile.is_open() )
		return(-2);
	// Read file content
	std::vector<unsigned char> data;
	data.insert(data.begin(),
	            std::istreambuf_iterator<char>(dataFile),
	            std::istreambuf_iterator<char>() );
	// Close file
	dataFile.close();
	
	mResponse->header()->setContentType("text/plain");

	std::string strData(data.begin(), data.end());
	cout << strData;
	
	return(0);
}
