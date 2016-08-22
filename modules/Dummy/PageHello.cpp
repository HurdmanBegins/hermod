/*
 * modDummy - An Hermod module for test and demo
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
#include "PageHello.hpp"

PageHello::PageHello(void)
    : Page()
{
	// Nothing to do
}

int PageHello::process(void)
{
	mResponse->header()->setContentType("text/html");

	cout << "<html>" << endl;
	cout <<     "<head><title>Hello World</title></head>" << endl;
	cout <<     "<body>" << endl;
	
	if (getArgCount() == 1)
		cout << "<h1>Hello World !</h1>" << endl;
	else
		cout << "<h1>Hello " << getArg(1) << " !</h1>" << endl;
	
	cout <<     "</body>" << endl;
	cout << "</html>" << endl;
	
	return(0);
}
