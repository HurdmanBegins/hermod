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
#include <stdexcept>
#include "Log.hpp"
#include "Request.hpp"

using namespace std;

Request::Request(FCGX_Request *req)
{
	mFcgiRequest = req;
	mPlugins = 0;
	mSession = 0;
}

Request::~Request()
{
//	Log::info() << "~Request" << Log::endl;
}

/*void Request::process(void)
{
	initSession();
	processPage();

	if (mSession && (mSession->isValid()) )
		mSession->save();
	if (mSession)
	{
		delete mSession;
		mSession = 0;
	}
}*/

std::string Request::getCookieByName(const std::string &name, bool allowEmpty = false)
{
	std::string value("");

	try {
		const char *c = FCGX_GetParam("HTTP_COOKIE", mFcgiRequest->envp);
		if (c == 0)
			throw runtime_error("No Cookie available");
		std::string qs(c);

		std::size_t pos = 0;
		while(1)
		{
			pos = qs.find(";", pos);
			std::string cookie = qs.substr(0, pos);

			std::size_t sep = cookie.find("=");
			if (sep == std::string::npos)
				continue;
			std::string cName  = cookie.substr(0, sep);
			std::string cValue = cookie.substr(sep + 1, std::string::npos);

			if ( ! cName.compare(name) )
			{
				value = cValue;
				break;
			}

			if (pos == std::string::npos)
				break;
		}
	} catch (std::exception &e) {
		Log::info() << "Request::getCookieByName " << e.what() << Log::endl;
	}

	if ( value.empty() && (allowEmpty == false) )
		throw runtime_error("Not Found");

	return value;
}

FCGX_Request *Request::getFCGX(void)
{
	return mFcgiRequest;
}

Request::Method Request::getMethod(void)
{
	//std::string method( FCGX_GetParam("REQUEST_METHOD", mFcgiRequest->envp) );
	std::string method = getParam("REQUEST_METHOD");
	if ( method.compare("OPTIONS") == 0 )
		return Option;
	else if ( method.compare("GET") == 0 )
		return Get;
	else if ( method.compare("POST") == 0 )
		return Post;
	else
		return Undef;
}

std::string Request::getParam (const std::string &name)
{
	std::string value;
	
	const char *p = FCGX_GetParam(name.c_str(), mFcgiRequest->envp);
	if (p)
		value = p;
	
	return value;
}

std::string Request::getUri(int n = 1)
{
	(void)n;
	const char *u = FCGX_GetParam("QUERY_STRING", mFcgiRequest->envp);
	std::string qs(u);
	
	return qs;
}

/*
void Request::initSession(void)
{
	SessionCache *sc = ::SessionCache::getInstance();

	Session *sess = 0;
	try {
		std::string sessId = getCookieByName("HERMOD_SESSION", false);
 		sess = sc->getById(sessId);
		if (sess == 0)
		{
			Log::debug() << "getSession() " << sessId << " not in cache." << Log::endl;
			sess = new Session();
			sess->load(sessId);
			if ( ! sess->isValid() )
			{
				Log::debug() << "getSession() " << sessId << " not valid too." << Log::endl;
				delete sess;
				sess = 0;
			}
		}
	} catch (std::exception &e) {
		Log::debug() << "getSession() Exception " << e.what() << Log::endl;
		if (sess)
		{
		        delete sess;
		        sess = 0;
		}
	}

	try {
		if (sess == 0)
		{
			sess = new Session();
			sess->create();
			mResponseHeader.addHeader("Set-Cookie", std::string("HERMOD_SESSION=") + sess->getId());
		}
	} catch (std::exception &e) {
		Log::debug() << "getSession() " << e.what() << Log::endl;
	}

	mSession = sess;

	return;
}
*/

void Request::setPlugins(std::vector<Module *> *plugins)
{
	mPlugins = plugins;
}
