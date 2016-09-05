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
#include "DB.hpp"

namespace hermod {
	namespace Database {

DB::DB()
{
	std::string dbUser("hermod");
	std::string dbPass("hermod");
	std::string dbDatabase("hermod");

	mDb = new odb::pgsql::database (dbUser, dbPass, dbDatabase, "localhost");
}

odb::pgsql::database *DB::getDB()
{
	return mDb;
}

	} // namespace Database
} // namespace hermod
/* EOF */
