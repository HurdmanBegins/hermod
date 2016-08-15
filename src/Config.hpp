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
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <cstddef> // std::size_t
#include <vector>
#include "config.h"

class ConfigGroup;
class ConfigKey;

class Config
{
public:
	static Config* getInstance();
	std::string get(const std::string &group, const std::string &key, size_t *pos = 0);
	void set(const std::string &group,
	         const std::string &key,
	         const std::string &value);
	void load (const std::string &filename);
protected:
	ConfigGroup *createGroup(const std::string &name);
	ConfigGroup *getGroup   (const std::string &name);
private:
	Config() {
		mGroups.empty();
	};
private:
	static Config* mInstance;
	std::vector<ConfigGroup *> mGroups;
};

class ConfigGroup
{
public:
	ConfigGroup();
	std::string getName();
	void setName(const std::string name);
	ConfigKey *createKey(const std::string &name, bool multiple = false);
	ConfigKey *getKey   (const std::string &name, size_t *pos = 0);
private:
	std::string mName;
	std::vector<ConfigKey *> mKeys;
};

class ConfigKey
{
public:
	ConfigKey();
	std::string getName();
	int         getPos();
	std::string getValue();
	void setName (const std::string name);
	void setPos  (int pos);
	void setValue(const std::string value);
private:
	std::string mName;
	std::string mValue;
	int mPos;
};

#endif
