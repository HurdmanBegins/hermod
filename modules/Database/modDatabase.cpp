/*
 * modDatabase - An Hermod module to use DBMS
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
#include "Module.hpp"
#include "modDatabase.hpp"

extern "C" Module* create_object()
{
	hermod::Database::ModDatabase *module;
	module = new hermod::Database::ModDatabase;
	
	return module;
}

extern "C" void destroy_object(Module *module)
{
	delete module;
}

namespace hermod {
	namespace Database {

ModDatabase::ModDatabase()
  : Module()
{
	// Set a name for this module
	setName("Database");
}

	} // namespace Database
} // namespace hermod
/* EOF */
