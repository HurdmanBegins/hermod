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

/**
 * @brief Default constructor
 *
 */
Module::Module(void)
{
	mHandle = 0;
}

/**
 * @brief Getter of the library handle
 *
 * Modules are dynamically loaded usind libdl. The pointer returned by dlopen()
 * is saved into Module object. This getHandle method is a getter to read back
 * the saved pointer.
 * 
 * @return void* Pointer to the library descriptor
 */
void *Module::getHandle(void)
{
	return mHandle;
}

/**
 * @brief Getter for the module name
 *
 * The module Name is a human readable string used to identify the Module. This
 * value is mainly used into config file to link one (or more) route to a page
 * exposed by this module.
 *
 * @return string Name of the module
 */
std::string Module::getName(void)
{
	return mName;
}

/**
 * @brief Setter for the library handle
 *
 * Modules are dynamically loaded usind libdl. This setHandle method is used to
 * save the pointer returned by dlopen().
 *
 * @param handle Pointer to the library descriptor
 */
void Module::setHandle(void *handle)
{
	mHandle = handle;
}

/**
 * @brief Setter for the module name
 *
 * @param name String contains the name of the module
 */
void Module::setName(const std::string &name)
{
	mName = name;
}

// ---------- Below, virtual methods used to specify Module interface ----------

void Module::freePage(Page *page)
{
	(void)page;
}

void Module::initRouter(Router *router)
{
	(void)router;
}

Page *Module::newPage(const std::string &name)
{
	(void)name;
	return NULL;
}
/* EOF */
