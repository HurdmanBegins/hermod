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
#include "Response.hpp"
#include "Router.hpp"
#include "SessionCache.hpp"

// Call to OS_LibShutdown() is needed to avoid fcgi leak
extern "C"
{
void OS_LibShutdown(void);
}

App*  App::mAppInstance = NULL;

App* App::getInstance()
{
	if ( ! mAppInstance)
	{
		mAppInstance = new App;
	}
	return mAppInstance;
}

void App::exec(void)
{
	FCGX_Request fcgiReq;
	
	try {
		FCGX_InitRequest(&fcgiReq, mFcgxSock, 0);
		
		mRunning = true;

		while(mRunning)
		{
			Request  *req;
			Response *rsp;
			
			if (FCGX_Accept_r(&fcgiReq) != 0)
			{
				Log::info() << "FastCGI interrupted during accept." << Log::endl;
				Log::sync();
				break;
			}
			// Instanciate a new Request
			req = new Request( &fcgiReq );
			req->setPlugins( &mPlugins );
			// Instanciate a new Response
			rsp = new Response( req );
			
			if (req->getMethod() == Request::Option)
			{
				Log::info() << "App: OPTION request received" << Log::endl;
				
				ResponseHeader *rh = rsp->header();
				rh->addHeader("Allow", "HEAD,GET,PUT,DELETE,OPTIONS");
				rh->addHeader("Access-Control-Allow-Headers", "access-control-allow-origin,x-requested-with");
				std::string corsMethod = req->getParam("HTTP_CORS_METHOD");
				if ( ! corsMethod.empty() )
					rh->addHeader("Access-Control-Allow-Method", corsMethod);
			}
			else if ( (req->getMethod() == Request::Get) ||
			          (req->getMethod() == Request::Post) )
			{
				RouteTarget *route = mRouter->find(req);
				if (route)
				{
					Log::info() << "App: Found a route for this request " << Log::endl;
					Page *page = route->newPage();
					if (page)
					{
						rsp->catchCout();

						try {
							page->setRequest( req );
							page->setReponse( rsp );
							page->initSession();
							page->process();
						} catch (std::exception &e) {
							Log::info() << "Request::process Exception " << e.what() << Log::endl;
						}

						rsp->releaseCout();

						route->freePage(page);
					}
					else
					{
						Log::info() << "App: Failed to load target page" << Log::endl;
						rsp->header()->setRetCode(404, "Not found");
					}
				}
				else
				{
					Log::info() << "App: No route for this request :(" << Log::endl;
					rsp->header()->setRetCode(404, "Not found");
				}
			}
			else
			{
				Log::info() << "App: Unknown method for this request :(" << Log::endl;
				rsp->header()->setRetCode(404, "Not found");
			}

			rsp->send();

			// Delete "Response" object at the end of the process
			delete rsp;
			rsp = NULL;
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
	
	try {
		// Free fcgi
		OS_LibShutdown();
		// Unload modules
		while(mPlugins.size())
			moduleUnload(mPlugins.size() - 1);
		// Clear the local Router
		delete mRouter;
		mRouter = NULL;
		// Clear the Session cache
		SessionCache::destroy();
		// Clear Config cache
		Config::destroy();
		// Clear Log layer
		Log::destroy();
	} catch(std::exception& e) {
		// ToDo: handle error ? !
	}
}

App* App::init(void)
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

	// Create a Router for this App
	mRouter = new Router;

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
	return getInstance();
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
	
		newModule = create();
		if (newModule == 0)
			throw std::runtime_error("Create failed");

		newModule->initRouter(mRouter);
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

	try {
		void (*destroy)(Module*);
		
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

void App::sigInt(void)
{
	FCGX_ShutdownPending();
}

/*	if ( ! mSession->isAuth() )
	{
		mResponseHeader.setRetCode(302, "Found");
		mResponseHeader.setContentType("");
		mResponseHeader.addHeader("Location", "/api/login");
		return(0);
	}*/
