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

Page::Page(void)
{
	mUri.clear();
	mRequest = 0;
	mResponseHeader = 0;
	mSession = 0;
}

void Page::setRequest(Request *obj)
{
	mRequest = obj;
	
	// Clear args of a previous request (if any)
	mArgs.clear();

//	std::istringstream qs(obj->getEnvironment().getQueryString());
//	for(std::string token; getline(qs, token, '/'); )
//		mArgs.push_back(token);
}

void Page::initReponse(ResponseHeader *obj)
{
	mResponseHeader = obj;
}
void Page::initSession(Session *sess)
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

string Page::getResponseHeader(void)
{
	return mResponseHeader->getHeader();
}
