/*
 * Hermod - Modular application framework
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
#ifndef MODULE_HPP
#define MODULE_HPP

#include <string>

class Page;
class Router;

using namespace std;

/**
 * Class used to handle modules
 *
 */
class Module
{
public:
	Module();
	void  *getHandle(void);
	string getName(void);
	void   setHandle(void *handle);
	void   setName(const std::string &name);
public:
	virtual void  initRouter(Router *router);
	virtual Page *newPage (const std::string &name);
	virtual void  freePage(Page *page);

protected:
	void *mHandle;
	std::string mName;
};
#endif
