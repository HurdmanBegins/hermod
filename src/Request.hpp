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

class Module;

class Request
{
public:
	enum Method { Undef, Get, Post, Option };
public:
	explicit Request(FCGX_Request *req);
	~Request();
	void setPlugins(std::vector<Module *> *plugins);
	unsigned int     countUriArgs(void);
	FCGX_Request    *getFCGX  (void);
	Request::Method  getMethod(void);
	std::string      getParam (const std::string &name);
	std::string getUri(unsigned int n);
	std::string getCookieByName(const std::string &name, bool allowEmpty);
	void        setUri(const std::string &route);
private:
	FCGX_Request  *mFcgiRequest;
	std::vector<Module *> *mPlugins;
	std::vector<std::string> mUri;
};
#endif
