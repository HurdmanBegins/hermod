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

Module::Module(void)
{
	mHandle = 0;
}

int Module::pageCount(void)
{
	return mPages.size();
}

Page *Module::getPage(int n)
{
	return mPages.at(n);
}

void *Module::getHandle(void)
{
	return mHandle;
}

void Module::setHandle(void *handle)
{
	mHandle = handle;
}
/* EOF */
