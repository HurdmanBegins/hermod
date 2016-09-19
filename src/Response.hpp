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
#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <sstream>
#include <streambuf>
#include "ResponseHeader.hpp"
#include "Content.hpp"

class Request;

/**
 * Class used to build and send CGI responses
 */
class Response {
public:
	explicit Response(Request *request = NULL);
	~Response();
	ResponseHeader *header();
	void catchCout  (void);
	void releaseCout(void);
	void send(void);
	void setContent(hermod::Content *content);
	void setRequest(Request *request);
private:
	Request          *mRequest;
	ResponseHeader    mHeader;
	hermod::Content  *mContent;
	std::streambuf   *mCoutBackup;
	std::stringstream mCoutBuffer;
};
#endif
