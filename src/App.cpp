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
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <dlfcn.h>  // dlopen() dlsym()

#include "App.hpp"
#include "Config.hpp"
#include "Log.hpp"
#include "Request.hpp"

using namespace std;

App::App(void)
{
	mPlugins.clear();
}

void App::exec(void)
{
	FCGX_Request fcgiReq;
	
	Request *req;
	
	try {
		FCGX_InitRequest(&fcgiReq, mFcgxSock, 0);

		while(FCGX_Accept_r(&fcgiReq) == 0)
		{
			req = new Request( &fcgiReq );
			req->setPlugins( &mPlugins );
			req->process();

			// Delete "Request" object at the end of the process
			delete req;
			req = 0;
			
			FCGX_Finish_r(&fcgiReq);
			
			// Flush Log
			Log::sync();
		} /* while */
	}
	catch(std::exception& e) {
		cout << "App::exception " << endl;
		cout << e.what() << endl;
	}
}

void App::init(void)
{
	Config *cfg = Config::getInstance();
	
	try {
		std::string cfgFile;
		cfgFile = cfg->get("global", "log_file");
		Log::setFile(cfgFile);
	} catch (std::exception& e) {
		// ToDo: print some message ?
	}

	// Init random number generator
	std::srand(std::time(0));

	// Load external modules
	size_t pos = 0;
	while(1)
	{
		std::string name;
		name = cfg->get("plugins", "load", &pos);
		if (name.empty())
			break;
		// Try to load the specified module
		moduleLoad( name );
		pos++;
	}

	// Initialize FCGI library
	FCGX_Init();
	mFcgxSock = FCGX_OpenSocket(":9000", 4);
	Log::info() << "Hermod (FCGI) started socket=" << mFcgxSock << Log::endl;

	Log::sync();
}

void App::moduleAdd(Module *mod)
{
        mPlugins.push_back(mod);
}

void App::moduleLoad(const std::string &name)
{
	Config *cfg = Config::getInstance();

	std::string dir = cfg->get("plugins", "directory");
	dir += name;

	void *handle = dlopen(dir.c_str(), RTLD_NOW|RTLD_GLOBAL);
	if (handle == 0)
	{
		Log::info() << "Load module " << name << " ";
		Log::info() << "failed : " << dlerror() << Log::endl;
		return;
	}
	
	Module *newModule;
	try {
		Module *(*create)(void);
	
		create = (Module*(*)(void))dlsym(handle, "create_object");
		if (create == 0)
			throw std::runtime_error("init function missing");
	
		newModule = (Module *)create();
		if (newModule == 0)
			throw std::runtime_error("Create failed");
	
	} catch (std::exception &e) {
		Log::info() << "Load module " << name << " ";
		Log::info() << "failed : " << e.what() << Log::endl;
		dlclose(handle);
		return;
	}
	Log::info() << "Load module " << name << Log::endl;
	
	newModule->setHandle(handle);
	mPlugins.push_back(newModule);
}


void App::moduleUnload(int n)
{
	Module *mod;
	void (*destroy)(Module*);

	try {
		mod = mPlugins.at(n);
		void *handle = mod->getHandle();
		destroy = (void(*)(Module*))dlsym(handle, "destroy_object");
		if (destroy == 0)
			throw std::runtime_error("Destroy failed");
		
		// Remove the Module from plugins -first-
		mPlugins.erase( mPlugins.begin() + n);
		// Then, destroy the plugin
		destroy(mod);
		// Unload/close the lib
		dlclose(handle);
	} catch (std::exception &e) {
		cerr << "MOD: " << e.what() << endl;
		return;
	}
}

/*	if ( ! mSession->isAuth() )
	{
		mResponseHeader.setRetCode(302, "Found");
		mResponseHeader.setContentType("");
		mResponseHeader.addHeader("Location", "/api/login");
		return(0);
	}*/
