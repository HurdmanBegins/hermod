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
#ifndef FILE_HPP
#define FILE_HPP
#include <string>

namespace hermod {
	namespace Files {
/**
 * @class File
 * @brief A generic class to handle files
 *
 */
class File
{
public:
	File();
	void addPath(const std::string &path);
	std::string getFullname(void);
	std::string getName(void);
	std::string getPath(void);
	std::string getRoot(void);
	bool isDirectory(void);
	void setName(const std::string &name);
	void setPath(const std::string &path);
	void setRoot(const std::string &root);
private:
	bool mPermissivePath;
	std::string mName;
	std::string mPath;
	std::string mRoot;
};

	} // namespace Files
} // namespace hermod
#endif
