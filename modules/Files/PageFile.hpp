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
#ifndef PAGEFILE_HPP
#define PAGEFILE_HPP

#include "Page.hpp"

namespace hermod {
	namespace Files {

class File;

class PageFile: public Page
{
public:
	PageFile();
	int process();
private:
	void directoryListing(File &dirFile);
	void fileDisplay(File &file);
};
	} // namespace Files
} // namespace hermod
#endif
