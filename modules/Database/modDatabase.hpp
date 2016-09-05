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
#ifndef MODDATABASE_HPP
#define MODDATABASE_HPP
#include "Module.hpp"

namespace hermod {
	namespace Database {

class ModDatabase : public Module
{
public:
	ModDatabase();
};

	} // namespace Database
} // namespace hermod
#endif
