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
#ifndef CONFIGKEY_HPP
#define CONFIGKEY_HPP
#include <string>

/**
 * @class ConfigKey
 * @brief This class allow to handle on configuration key
 *
 */
class ConfigKey
{
public:
	explicit ConfigKey(const std::string &name);
	bool        getBoolean(bool def);
	int         getInteger(void);
	std::string getName();
	int         getPos();
	std::string getValue();
	void setPos  (int pos);
	void setValue(const std::string &value);
private:
	std::string mName;
	std::string mValue;
	int mPos;
};

#endif
