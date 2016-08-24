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
#include "Config.hpp"
#include "Log.hpp"
#include "Router.hpp"
#include "Request.hpp"

Router::Router(void)
{
	mTargets.clear();
}

Router::~Router()
{
	while(mTargets.size())
	{
		RouteTarget *target = mTargets.back();
		mTargets.pop_back();
		delete target;
	}
}

RouteTarget *Router::createTarget(Module *module)
{
	RouteTarget *target = new RouteTarget;
	target->setModule(module);
	mTargets.push_back(target);
	
	return target;
}

RouteTarget *Router::find(Request *r)
{
	RouteTarget *target = NULL;
	ConfigKey   *k      = NULL;
	Config      *cfg = Config::getInstance();
	
	std::string uri = r->getUri(0);
	
	try {
		for(int i = 0; ;++i)
		{
			k = cfg->getKey("route", i);
			if (k == NULL)
				throw std::runtime_error("No route found into config !");
			
			std::string routeUri = k->getName();
			if ( uri.compare(0, routeUri.size(), routeUri) == 0)
				break;
		}
	} catch (std::exception &e) {
		Log::info() << "Router error: " << e.what() << Log::endl;
		return NULL;
	}

	// If no valid route found :( Nothing more to do
	if (k == NULL)
	{
		Log::info() << "Router: Not found any route for " << uri << Log::endl;
		return NULL;
	}

	try {
		// Split rule string to find module name and page name
		std::size_t sepPos = k->getValue().find(':');
		if (sepPos == std::string::npos)
			throw std::runtime_error("Malformed route");
		// Extract name of the module from rule
		std::string modName  = k->getValue().substr(0, sepPos);
		// Extract name of the page from rule
		std::string pageName = k->getValue().substr(sepPos + 1, std::string::npos);

		std::vector<RouteTarget *>::iterator it;
		for (it = mTargets.begin(); it != mTargets.end(); ++it)
		{
			// Test if the target is valid/enabled
			if ( ! (*it)->isEnabled() )
				continue;
			// Test if Module name match
			if (modName != (*it)->getModule()->getName())
				continue;
			// Test if page name match
			if (pageName != (*it)->getName())
				continue;
			// Yes :) A valid RouteTarget has been found
			target = *it;
			break;
		}
		
		if (target == NULL)
		{
			Log::info() << "Router: No target for the route (";
			Log::info() << modName << ":" << pageName << ")" << Log::endl;
		}

	} catch (std::exception &e) {
		Log::info() << "Router error: " << e.what() << Log::endl;
		return NULL;
	}

	// If a valid route ; and a valid target found
	if (k && target)
	{
		// Update Request URI and args
		r->setUri( k->getName() );
	}

	return target;
}

void Router::removeTarget(RouteTarget *target)
{
	std::vector<RouteTarget *>::iterator it;
	for (it = mTargets.begin(); it != mTargets.end(); ++it)
	{
		if ( (*it) != target )
			continue;
		RouteTarget *target = *it;
		// Remove the selected element from the list ...
		mTargets.erase(it);
		// ... then, delete it
		delete target;
		
		// Element has been removed, nothing more to do
		break;
	}
}
/* EOF */
