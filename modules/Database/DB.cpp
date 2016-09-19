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

DB::DB(const std::string &name)
  : mName(name), mDbName("hermod")
{
	mDb = 0;
	mIdentUser.clear();
	mIdentPass.clear();
}

DB::~DB()
{
	if (mDb)
	{
		delete mDb;
		mDb = 0;
	}
}

odb::pgsql::database *DB::get()
{
	if (mDb == 0)
	{
		mDb = new odb::pgsql::database (mIdentUser, mIdentPass, mDbName, "localhost");
		if (mDb == 0)
			throw 1;
	}
	return mDb;
}

std::string DB::getName(void)
{
	return mName;
}

void DB::setDbName(const std::string &name)
{
	mDbName = name;
}

void DB::setIdent(const std::string &user, const std::string &pass)
{
	mIdentUser = user;
	mIdentPass = pass;
}

	} // namespace Database
} // namespace hermod
/* EOF */
