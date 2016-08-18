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
#include <iostream>
#include <string>
#include "Module.hpp"
#include "Router.hpp"
#include "Page.hpp"

Module::Module(void)
{
	mHandle = 0;
}

void Module::freePage(Page *page)
{
	(void)page;
}

void Module::initRouter(Router *router)
{
	(void)router;
}

int Module::pageCount(void)
{
	return mPages.size();
}

Page *Module::getPage(int n)
{
	return mPages.at(n);
}

Page *Module::newPage(const std::string &name)
{
	(void)name;
	return NULL;
}

void *Module::getHandle(void)
{
	return mHandle;
}

std::string Module::getName(void)
{
	return mName;
}

void Module::setHandle(void *handle)
{
	mHandle = handle;
}

void Module::setName(const std::string &name)
{
	mName = name;
}
/* EOF */
