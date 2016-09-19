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
#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP
#include <vector>
#include "File.hpp"

namespace hermod {
	namespace Files {

/**
 * @class Directory
 * @brief This class inherit from File to handle directories
 *
 */
class Directory : public File
{
public:
	Directory();
	explicit Directory(File &source);
	~Directory();
	File *at(int index);
	void  clear(void);
	int   count(void);
protected:
	void refresh(void);
private:
	bool mValidList;
	std::vector<File *> mFiles;
};

	} // namespace Files
} // namespace hermod
#endif
