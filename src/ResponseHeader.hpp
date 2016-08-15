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
#ifndef RESPONSEHEADER_HPP
#define RESPONSEHEADER_HPP

#include <map>

using namespace std;

class ResponseHeader {
public:
	ResponseHeader();
	void addHeader(string key, string value);

	void setContentType(string type);
	void setRetCode(int code, string reason);

	string getHeader(void);

private:
	int    mRetCode;
	string mRetReason;
	string mContentType;
	std::map <string, string> mHeaders;
};
#endif
