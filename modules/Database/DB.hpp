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
#ifndef DB_HPP
#define DB_HPP

#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/pgsql/database.hxx>

namespace hermod {
	namespace Database {

class DB
{
public:
	DB();
	odb::pgsql::database *getDB();
private:
	odb::pgsql::database *mDb;
};

	} // namespace Database
} // namespace hermod
#endif
