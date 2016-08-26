/*
 * modFiles - An Hermod module to access static files
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
#ifndef MODFILES_HPP
#define MODFILES_HPP
#include "Module.hpp"
#include "Router.hpp"

class Page;

namespace hermod {
	namespace Files {

class ModFiles : public Module
{
public:
	ModFiles();
	void   freePage(Page *page);
	void   initRouter(Router *router);
	Page  *newPage(const std::string &name);
};

	} // namespace Files
} // namespace hermod
#endif
