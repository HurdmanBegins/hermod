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
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Config.hpp"

Config* Config::mInstance = NULL;  

void Config::destroy(void)
{
	if ( ! mInstance)
		return;
	// Delete all config groups
	while( mInstance->mGroups.size() )
	{
		ConfigGroup *g = mInstance->mGroups.back();
		mInstance->mGroups.pop_back();
		delete g;
	}
	// Delete singleton object
	delete mInstance;
	mInstance = NULL;
}

Config* Config::getInstance()
{
	if ( ! mInstance)
	{
		mInstance = new Config;
	}
	return mInstance;
}

#ifdef C_PTR
std::string Config::getKey(char *group, char *key)
{
	std::string g = std::string(group);
	std::string k = std::string(k);
	return getKey(g, k);
}
#endif

ConfigGroup *Config::createGroup(const std::string &name)
{
	ConfigGroup *grp;
	
	// Search if the group already exists
	grp = getGroup(name);
	if (grp)
		return grp;
	
	// Create a new group
	try {
		grp = new ConfigGroup;
	} catch (std::exception& e) {
		return NULL;
	}
	
	grp->setName(name);
	mGroups.push_back(grp);
	
	return grp;
}

ConfigGroup *Config::getGroup(const std::string &name)
{
	size_t nbGroups;
	
	nbGroups = mGroups.size();
	
	// Look into the list of known groups
	for (size_t i = 0; i < nbGroups; i++)
	{
		ConfigGroup *grp = mGroups.at(i);
		if (name.compare(grp->getName()) == 0)
			return grp;
	}
	return NULL;
}

std::string Config::get(const std::string &group, const std::string &key, size_t *pos)
{
	ConfigGroup *g;
	ConfigKey   *k;
	
	// Get the specified group
	g = getGroup(group);
	if (g == NULL)
		return std::string();
	
	// Get the specified key into the group
	k = g->getKey(key, pos);
	if (k == NULL)
		return std::string();
	
	return k->getValue();
}

ConfigKey *Config::getKey(const std::string &group, int index)
{
	ConfigGroup *g;
	
	// Get the specified group
	g = getGroup(group);
	if (g == NULL)
		return NULL;
	
	return g->getKey(index);
}

void Config::load(const std::string &filename)
{
	std::fstream cfgFile;
	cfgFile.open(filename.c_str(), std::ios::in);
	if ( ! cfgFile.is_open())
		throw std::runtime_error("Config: Could not open the file!");

	ConfigGroup *group;

	std::string lineData;
	while ( getline(cfgFile, lineData) )
	{
		size_t found;
		found = lineData.find_first_not_of(" \t");
		if ( (found != std::string::npos) && (found != 0) )
			lineData.erase(0, found);
		if (lineData[0] == '[')
		{
			found = lineData.find(']');
			if (found == std::string::npos)
				continue;
			// Get or create this config group
			std::string grpName;
			grpName = lineData.substr(1, found - 1);
			group = createGroup(grpName);
			continue;
		}
		if (lineData[0] == '#')
		{
			// This line is a comment
			continue;
		}
		// Search key/value separator
		found = lineData.find('=');
		if (found == std::string::npos)
			continue;
		// Extract the key/value pair
		std::string key   ( lineData.substr(0, found) );
		std::string value ( lineData.substr(found+ 1, std::string::npos) );
		// Create a new config key
		ConfigKey *k = group->createKey(key, true);
		// Save the specified value
		k->setValue(value);
		std::cerr << "Config load group=" << group->getName() << " ";
		std::cerr << "key="   << key   << " ";
		std::cerr << "value=" << value << std::endl;
	}
	cfgFile.close();
}

void Config::set(const std::string &group,
                 const std::string &key,
                 const std::string &value)
{
	ConfigGroup *g;
	ConfigKey   *k;
	
	// Get or create specified group
	g = createGroup(group);
	// Get or create specified key
	k = g->createKey(key);
	
	k->setValue(value);
}
                                          
// -------------------- GROUPs -------------------- //
ConfigGroup::ConfigGroup()
{
	mName.clear();
	mKeys.clear();
}

ConfigGroup::~ConfigGroup()
{
	while(mKeys.size())
	{
		ConfigKey *k = mKeys.back();
		mKeys.pop_back();
		delete k;
	}
}

std::string ConfigGroup::getName()
{
	return mName;
}
void ConfigGroup::setName(const std::string &name)
{
	mName = name;
}

ConfigKey *ConfigGroup::createKey(const std::string &name, bool multiple)
{
	ConfigKey *key;
	
	if (multiple == false)
	{
		// Search if the key already exists
		key = getKey(name);
		if (key)
			return key;
	}
	
	// Create a new key
	try {
		key = new ConfigKey;
	} catch (std::exception& e) {
		return NULL;
	}
	
	key->setName(name);
	mKeys.push_back(key);
	
	key->setPos(mKeys.size() - 1);
	
	return key;
}

ConfigKey *ConfigGroup::getKey(const std::string &name, size_t *pos)
{
	size_t nbKeys;
	
	nbKeys = mKeys.size();
	
	int first = 0;
	if (pos)
		first = *pos;
	
	// Look into the list of known keys
	for (size_t i = first; i < nbKeys; i++)
	{
		ConfigKey *key = mKeys.at(i);
		if (name.compare(key->getName()) == 0)
		{
			if (pos)
				*pos = i;
			return key;
		}
	}
	return NULL;
}

ConfigKey *ConfigGroup::getKey(unsigned int index)
{
	if (index >= mKeys.size())
		return NULL;
	
	return mKeys.at(index);
}

// -------------------- KEYs -------------------- //
ConfigKey::ConfigKey()
{
	mPos = 0;
	mName.clear();
	mValue.clear();
}

std::string ConfigKey::getName()
{
	return mName;
}
void ConfigKey::setName(const std::string &name)
{
	mName = name;
}

int ConfigKey::getPos(void)
{
	return mPos;
}
void ConfigKey::setPos(int pos)
{
	mPos = pos;
}

std::string ConfigKey::getValue()
{
	return mValue;
}
void ConfigKey::setValue(const std::string &value)
{
	mValue = value;
}
