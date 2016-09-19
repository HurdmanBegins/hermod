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
#ifndef ROUTETARGET_HPP
#define ROUTETARGET_HPP

#include <string>
#include <vector>

class Page;

namespace hermod {

class Module;

class RouteTarget
{
public:
	RouteTarget   (void);
	void    disable(void);
	void    enable(void);
	bool    isEnabled(void);
	Module *getModule(void);
	const std::string &getName(void);
	void setModule(Module *module);
	void setName  (const std::string &name);
	// Handle Pages
	Page   *newPage (void);
	void    freePage(Page *page);
private:
	bool         mValid;
	std::string  mName;
	Module      *mModule;
};

} // namespace hermod
#endif
