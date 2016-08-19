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
#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <fcgio.h>
#include "Module.hpp"
#include "Page.hpp"
#include "ResponseHeader.hpp"
#include "Session.hpp"

class Module;

class Request
{
public:
	enum Method { Undef, Get, Post, Option };
public:
	explicit Request(FCGX_Request *req);
	~Request();
//	void process(void);
	void setPlugins(std::vector<Module *> *plugins);
	FCGX_Request    *getFCGX  (void);
	Request::Method  getMethod(void);
	std::string      getParam (const std::string &name);
	std::string getUri(int n);
private:
	std::string getCookieByName(const std::string &name, bool allowEmpty);
//	void initSession(void);
private:
	FCGX_Request  *mFcgiRequest;
	ResponseHeader mResponseHeader;
	std::vector<Module *> *mPlugins;
	Session       *mSession;
};
#endif
