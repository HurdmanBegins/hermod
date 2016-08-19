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
#include "Page.hpp"
#include "Request.hpp"

Page::Page(void)
{
	mUri.clear();
	mRequest  = 0;
	mResponse = 0;
	mSession  = 0;
}

void Page::setRequest(Request *obj)
{
	mRequest = obj;
	
	// Clear args of a previous request (if any)
	mArgs.clear();
	// Compute the argument list
	std::istringstream qs(obj->getParam("QUERY_STRING"));
	for(std::string token; getline(qs, token, '/'); )
		mArgs.push_back(token);
}

void Page::setReponse(Response *obj)
{
	mResponse = obj;
}

void Page::setSession(Session *sess)
{
	mSession = sess;
}

std::string Page::getUri(void)
{
	return mUri;
}

int    Page::getArgCount(void)
{
	return mArgs.size();
}
string Page::getArg(int n)
{
	return mArgs.at(n);
}
