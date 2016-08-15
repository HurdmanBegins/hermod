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
#ifndef SESSION_HPP
#define SESSION_HPP
#include <string>
#include <map>

using namespace std;

class Session;

class SessionCache
{
public:
	static SessionCache* getInstance();
	Session *getById(const std::string &id);
private:
	SessionCache();
	static SessionCache* mInstance;
};

class Session
{
public:
	Session();
	void create(void);
	void load(string key);
	void save(void);
	void auth(unsigned long id, string user);
	std::string getKey   (const std::string &key);
	int         getKeyInt(const std::string &key);
	void setKey(const std::string &key, const std::string &value);
	void setKey(const std::string &key, unsigned long value);
	void removeKey(const std::string &key);
	void clearFileKey(void);
public:
	string getId  (void);
	bool   isNew  (void);
	bool   isValid(void);
	int    isAuth (void);
private:
	int    mCount;
	bool   mIsNew;
	bool   mValid;
	string mKey;
	string mFilename;
	std::map <string, string> mCache;
};
#endif