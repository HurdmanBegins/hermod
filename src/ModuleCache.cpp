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
#include "ModuleCache.hpp"
#include "Config.hpp"
#include "Log.hpp"
#include <dlfcn.h>

namespace hermod {

/**
 * @brief Default constructor
 *
 */
ModuleCache::ModuleCache()
{
}

/**
 * @brief Default destructor
 *
 */
ModuleCache::~ModuleCache()
{
}

/**
 * @brief Unload all modules of this cache
 *
 */
void ModuleCache::clear(void)
{
	while( mModules.size() )
		unload( mModules.size() - 1 );
}

/**
 * @brief Find a module identified by his name
 *
 * @return Module* Pointer to the module object (or NULL)
 */
Module *ModuleCache::find(const std::string &name)
{
	Module *module = 0;
	
	std::vector<Module *>::iterator it;
	for (it = mModules.begin(); it != mModules.end(); ++it)
	{
		if (name.compare( (*it)->getName() ) == 0)
		{
			module = *it;
			break;
		}
	}
	
	return module;
}

Module * ModuleCache::load(const std::string &name)
{
	Config *cfg = Config::getInstance();
	
	std::string fullname = cfg->get("plugins", "directory");
	fullname += name;
	
	void *handle = dlopen(fullname.c_str(), RTLD_NOW|RTLD_GLOBAL);
	if (handle == 0)
	{
		Log::warning() << "Load module " << name << " ";
		Log::warning() << "failed : " << dlerror() << Log::endl;
		return 0;
	}
	
	Module *newModule = 0;
	try {
		Module *(*create)(void);
		
		create = (Module*(*)(void))dlsym(handle, "create_object");
		if (create == 0)
			throw std::runtime_error("init function missing");
		
		newModule = create();
		if (newModule == 0)
			throw std::runtime_error("Create failed");
	} catch (std::exception &e) {
		Log::warning() << "Load module " << name << " ";
		Log::warning() << "failed : " << e.what() << Log::endl;
		dlclose(handle);
		return 0;
	}
	
	newModule->setHandle(handle);
	newModule->setCache( this );
	
	mModules.push_back(newModule);
	
	return newModule;
}

void ModuleCache::unload(int index)
{
	Module *mod;
	
	try {
		void (*destroy)(Module*);
		
		mod = mModules.at(index);
		void *handle = mod->getHandle();
		destroy = (void(*)(Module*))dlsym(handle, "destroy_object");
		if (destroy == 0)
			throw std::runtime_error("Destroy failed");
		
		// Remove the Module from plugins -first-
		mModules.erase( mModules.begin() + index);
		// Then, destroy the plugin
		destroy(mod);
		// Unload/close the lib
		dlclose(handle);
	} catch (std::exception &e) {
		Log::warning() << "MOD: " << e.what() << Log::endl;
	}
	
	return;
}

} // namespace hermod
/* EOF */
