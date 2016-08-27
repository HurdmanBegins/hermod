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
#include "Config.hpp"
#include "Log.hpp"
#include "Page.hpp"
#include "Request.hpp"
#include "Session.hpp"
#include "SessionCache.hpp"

using namespace hermod;

Page::Page(void)
{
	mRequest  = NULL;
	mResponse = NULL;
	mSession  = NULL;
	mUseSession = false;
}

/**
 * @brief Get Uri (or argument) of the request
 *
 * This method allow to get a part of the original URI, after analysis by
 * router. The first item (n=0) contains the route, and other items (n>0)
 * contains other words of the URI separated by '/'. This method is just a
 * wrapper to Request object, and can be overloaded by specific page.
 *
 * @param n Position of the requested element (0 for uri)
 * @return string Value of the requested element
 */
string Page::getArg(int n)
{
	return mRequest->getUri(n);
}

/**
 * @brief Get the number of arguments found into the requested URI
 *
 * This method is just a wrapper to countUriArs() of Request object. Using this
 * method instead of original is usefull when overload by a specific page.
 *
 * @return integer Number of arguments into URI
 */
int Page::getArgCount(void)
{
	return mRequest->countUriArgs();
}

/**
 * @brief Create a generic Content and insert it into Page Response
 *
 * @return Content* Pointer to the newly allocated Content
 */
Content *Page::initContent(void)
{
	if ( ! mResponse)
		return NULL;
	
	Content *content = new Content();
	if ( ! content)
		throw runtime_error("Failed to allocate Content");
	
	mResponse->setContent(content);
	
	return content;
}

void Page::initSession(void)
{
	// Test if this page require session
	if ( ! mUseSession)
		return;
	// Test if session already init
	if (mSession)
		return;
	
	Config       *cfg  = Config::getInstance();
	SessionCache *sc   = SessionCache::getInstance();
	Session      *sess = NULL;
	std::string   sessId;
	
	std::string cfgSessionMode( cfg->get("global", "session_mode") );
	if (cfgSessionMode.compare("cookie") == 0)
	{
		Log::info() << "Page: init Session using cookie" << Log::endl;
		// Find Session ID using cookie
		try {
			std::string cookieName;
			// Try to get the cookie name from config
			cookieName = cfg->get("global", "session_cookie");
			// If this parameter is absent
			if (cookieName.empty())
				cookieName = "HERMOD_SESSION";
			try {
				sessId = mRequest->getCookieByName(cookieName, false);
			} catch (...) {
			}
			Log::info() << "Page: cookie " << cookieName;
			Log::info() << " = " << sessId << Log::endl;
			sess = sc->getById(sessId);
			if (sess)
			{
				Log::info() << "Page: Session found" << Log::endl;
			}
			else
			{
				Log::info() << "Page: Session not found" << Log::endl;
				sess = sc->create();
				if (sess == NULL)
					throw runtime_error("Failed to create a new session");
				std::string cookie( cookieName );
				cookie += "=" + sess->getId();
				mResponse->header()->addHeader("Set-Cookie", cookie);
			}
			mSession = sess;
		} catch (...) {
			Log::info() << "Page: Session cookie EXCEPTION" << Log::endl;
		}
	}
	else if (cfgSessionMode.compare("token") == 0)
	{
		// Second, try to find Session ID using token
		try {
			//
		} catch (...) {
		}
	}
	else
	{
		Log::info() << "Page: Could not load session, unknown mode ";
		Log::info() << cfgSessionMode << Log::endl;
	}
}

void Page::setRequest(Request *obj)
{
	mRequest = obj;
}

void Page::setReponse(Response *obj)
{
	mResponse = obj;
}

bool Page::useSession(void)
{
	return mUseSession;
}
/* EOF */
