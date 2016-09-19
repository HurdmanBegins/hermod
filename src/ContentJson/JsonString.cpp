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
#include <string>
#include <sstream>
#include "JsonString.hpp"

namespace hermod {
	namespace contentJson {

/**
 * @brief Constructor
 *
 */
JsonString::JsonString(const std::string &str)
  : mString(str)
{
	// Nothing to do
}

/**
 * @brief Render the JSON string
 *
 */
void JsonString::renderBody(void)
{
	std::ostringstream ss;
	
	ss << "\"" << mString << "\"";
	
	renderAppend( ss.str() );
}

	} // namespace contentJson
} // namespace hermod
/* EOF */
