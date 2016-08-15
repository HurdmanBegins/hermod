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
#include <map>
#include <string>
#include <sstream>
#include "ResponseHeader.hpp"

using namespace std;

ResponseHeader::ResponseHeader()
{
	mRetCode = 200;
	mContentType = "text/plain";
}

void ResponseHeader::addHeader(string key, string value)
{
	std::map<std::string, std::string>::iterator it;
	
	it = mHeaders.find(key.c_str());
	if (it != mHeaders.end())
		mHeaders.erase (it);
	mHeaders[key] = value;
}

void ResponseHeader::setContentType(string type)
{
	mContentType = type;
}

void ResponseHeader::setRetCode(int code, string reason)
{
	mRetCode   = code;
	mRetReason = reason;
}

string ResponseHeader::getHeader(void)
{
	std::ostringstream oss;
	std::string h;
	
	if (mRetCode != 200)
	{
		oss << mRetCode;
		h += "Status: " + oss.str() + " ";
		h += mRetReason + "\n";
	}
	
	if (mContentType != "")
		h += "Content-type: " + mContentType + "\n";
	
	std::map<std::string, std::string>::iterator it;
	for (it = mHeaders.begin(); it != mHeaders.end(); it++)
	{
		h += it->first +": " + it->second + "\n";
	}
	
	// Add an empty line for the end of header
	h += "\n";
	
	return h;
}
