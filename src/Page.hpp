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
#ifndef PAGE_HPP
#define PAGE_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Response.hpp"
#include "Session.hpp"

class Request;

using namespace std;

class Page
{
public:
	Page();
	void   setRequest(Request   *obj);
	void   setReponse(Response  *obj);
	void   initSession(void);
	
	std::string getUri(void);
	
	bool   useSession(void);
public:	
	virtual string getArg(int n);
	virtual int getArgCount(void);
	virtual int process() = 0;
protected:
	bool      mUseSession;
	Request  *mRequest;
	Response *mResponse;
	Session  *mSession;
};
#endif
