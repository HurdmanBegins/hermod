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

void Request::process(void)
{
	std::streambuf *backup;
	std::stringstream buffer;
	
	// back up cout's streambuf
	backup = std::cout.rdbuf();
	// Clear the intermediate buffer
	buffer.str(std::string());
	// Redirect cout to intermediate buffer
	std::cout.rdbuf(buffer.rdbuf());

	try {
		processHeaders();
		
		std::string method( FCGX_GetParam("REQUEST_METHOD", mFcgiRequest->envp) );
		if ( method.compare("OPTIONS") == 0 )
			processOptions();
		else
		{
			initSession();
			processPage();
		}

		if (mSession && (mSession->isValid()) )
			mSession->save();
		if (mSession)
		{
			delete mSession;
			mSession = 0;
		}

	} catch (std::exception &e) {
		Log::info() << "Request::process Exception " << e.what() << Log::endl;
	}

	std::cout.rdbuf(backup);

	FCGX_Stream *fout = mFcgiRequest->out;
	FCGX_PutS(mResponseHeader.getHeader().c_str(), fout);
	// fout << getResponseContent();
	FCGX_PutS(buffer.str().c_str(), fout);
}

/*Page *Request::findPageByName(const std::string &name)
{
	for (unsigned int i = 0; i < mPlugins->size(); i++)
	{
		Module *mod = mPlugins->at(i);
		for (int j = 0; j < mod->pageCount(); j++)
		{
			Page *pg = mod->getPage(j);
			std::string pgUri = pg->getUri();
			if (name.compare(0, pgUri.size(), pgUri) == 0)
				return pg;
		}
	}
	return 0;
}
*/
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

std::string Request::getUri(int n = 1)
{
	(void)n;
	const char *u = FCGX_GetParam("QUERY_STRING", mFcgiRequest->envp);
	std::string qs(u);
	
	return qs;
}

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

void Request::processHeaders(void)
{
	// Process "Origin" header
	std::string o( FCGX_GetParam("HTTP_ORIGIN", mFcgiRequest->envp) );
	if ( ! o.empty() )
		mResponseHeader.addHeader("Access-Control-Allow-Origin", o);

	// Allow credentials control
	mResponseHeader.addHeader("Access-Control-Allow-Credentials", "true");
}

void Request::processOptions(void)
{
	mResponseHeader.addHeader("Allow", "HEAD,GET,PUT,DELETE,OPTIONS");
	mResponseHeader.addHeader("Access-Control-Allow-Headers", "access-control-allow-origin,x-requested-with");
	
	const char *c = FCGX_GetParam("HTTP_CORS_METHOD", mFcgiRequest->envp);
	if (c)
	{
	        std::string allowMethod(c);
        	mResponseHeader.addHeader("Access-Control-Allow-Method", allowMethod);
        }
}

void Request::processPage()
{
	std::string uri;

	uri = getUri(1);
	
	Log::info() << "[ " << mSession << "] request " << uri << Log::endl;
	
	// Search the requested page into modules
	// GSG Page *pg = findPageByName(uri);
	Page *pg = 0;
	if (pg)
	{
		pg->setRequest( this );
		pg->initReponse( &mResponseHeader );
		pg->initSession( mSession );
		pg->process();
	}
	// Else, requested page has not been found
	else
	{
        Log::info() << "Not found " << Log::endl;
		// Search if "404" page is available
		// GSG pg = findPageByName("404");
		pg = 0;
		if (pg)
		{
			// Process and send "404"
			pg->setRequest( this );
			pg->initReponse( &mResponseHeader );
			pg->initSession( mSession );
			pg->process();
		}
		else
		{
			mResponseHeader.setRetCode(404, "Not found");
			Log::info() << "[ " << mSession << "] Page not found." << Log::endl;
		}
	}
}

void Request::setPlugins(std::vector<Module *> *plugins)
{
	mPlugins = plugins;
}
