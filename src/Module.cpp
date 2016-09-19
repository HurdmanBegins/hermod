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

namespace hermod {

/**
 * @brief Default constructor
 *
 */
Module::Module(ModuleCache *cache)
{
	mHandle  = 0;
	mModules = cache;
}

/**
 * @brief Get access to the cache that manage this module
 *
 * To easily manage module, they can be put into a "cache" object. This cache
 * is able to create, load (and unload) them and maintain a list of known
 * modules. This getter method allow to get a pointer to the cache that "own"
 * the current object.
 *
 * @return ModuleCache* Pointer to the parent cache
 */
ModuleCache *Module::getCache(void)
{
	if (mModules == 0)
		throw 1;
	
	return mModules;
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
 * @brief Set the ModuleCache where this module is registered
 *
 * @param cache Pointer to the parent ModuleCache
 */
void Module::setCache (ModuleCache *cache)
{
	mModules = cache;
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

} // namespace hermod
/* EOF */
