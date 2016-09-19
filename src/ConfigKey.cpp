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
#include <cstdlib>
#include "ConfigKey.hpp"

namespace hermod {

/**
 * @brief Default constructor for a config key object
 *
 */
ConfigKey::ConfigKey(const std::string &name) : mName(name)
{
	mPos  = 0;
	mValue.clear();
}

/**
 * @brief Get a boolean value of the key
 *
 * @return bool A boolean value based on key string
 */
bool ConfigKey::getBoolean(bool def = false)
{
	if ( (mValue.compare("yes") == 0) ||
	     (mValue.compare("YES") == 0) ||
	     (mValue.compare("on")  == 0) ||
	     (mValue.compare("ON")  == 0) )
	{
		return true;
	}

	if ( (mValue.compare("no")  == 0) ||
	     (mValue.compare("NO")  == 0) ||
	     (mValue.compare("off") == 0) ||
	     (mValue.compare("OFF") == 0) )
	{
		return false;
	}

	return def;
}

/**
 * @brief Get an integer value of the key
 *
 * @return integer An integer value based on key string
 */
int ConfigKey::getInteger(void)
{
	int value = atoi(mValue.c_str());

	return value;
}

/**
 * @brief Get the key name
 *
 * @return string The current key name
 */
std::string ConfigKey::getName()
{
	return mName;
}

/**
 * @brief Get the key position into config
 *
 * When a key have multiple occurrences, the 'position' index is used to
 * identify each of them into a group. When a key have a single value (the
 * main case) this member is not used.
 *
 * @return integer The current key index
 */
int ConfigKey::getPos(void)
{
	return mPos;
}

/**
 * @brief Set the key position into config
 *
 * When a key have multiple occurrences, the 'position' index is used to
 * identify each of them into a group. When a key have a single value (the
 * main case) this member is not used.
 *
 * @param pos The new key index
 */
void ConfigKey::setPos(int pos)
{
	mPos = pos;
}

/**
 * @brief Get the key value as string
 *
 * @return string The current key value
 */
std::string ConfigKey::getValue()
{
	return mValue;
}

/**
 * @brief Set the value of this key
 *
 * @param value The new value to save
 */
void ConfigKey::setValue(const std::string &value)
{
	mValue = value;
}

} // namespace hermod
/* EOF */
