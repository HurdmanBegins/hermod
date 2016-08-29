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
#ifndef CONTENTJSON_STRING_HPP
#define CONTENTJSON_STRING_HPP
#include <string>
#include "JsonElement.hpp"

namespace hermod {
	namespace contentJson {

/**
 * @class JsonString
 * @brief Class to handle a JSON string
 *
 */
class JsonString : public JsonElement {
public:
	explicit JsonString(const std::string &str);
	void renderBody(void);
private:
	std::string mString;
};

	} // namespace contentJson
} // namespace hermod
#endif
