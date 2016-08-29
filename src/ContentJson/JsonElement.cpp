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
#include "JsonElement.hpp"

namespace hermod {
	namespace contentJson {

/**
 * @brief Default constructor
 *
 */
JsonElement::JsonElement()
{
	mName.clear();
	mRenderBuffer = 0;
}

/**
 * @brief Default destructor
 *
 */
JsonElement::~JsonElement()
{
}

/**
 * @brief Get the name of this element
 *
 * @return string The current name of element
 */
std::string JsonElement::getName(void)
{
	return mName;
}

/**
 * @brief Append a string to the output buffer
 *
 * @param str Reference to the string to append
 */
void JsonElement::renderAppend(const std::string &str)
{
	// Sanity check
	if (mRenderBuffer == 0)
		return;
	
	std::copy(str.c_str(),
	          str.c_str()+str.length(),
	          std::back_inserter(*mRenderBuffer));
}

/**
 * @brief This method produce the JSON (text) code of this object
 *
 */
void JsonElement::render(void)
{
	// Render a first part named "head"
	renderHead();
	// Render a second part named "body"
	renderBody();
	// Render a third part named "tail"
	renderTail();
}

/**
 * @brief Default render for the "head" of this element
 *
 */
void JsonElement::renderHead(void)
{
}

/**
 * @brief Default render for the "body" of this element
 *
 */
void JsonElement::renderBody(void)
{
}

/**
 * @brief Default rendre for the "tail" of this element
 *
 */
void JsonElement::renderTail(void)
{
}

/**
 * @brief Set the name of this object
 *
 * @param name New name to register
 */
void JsonElement::setName(const std::string &name)
{
	mName = name;
}

/**
 * @brief Set the output buffer to use for rendering element
 *
 * @param buffer Pointer to the output buffer
 */
void JsonElement::setRenderBuffer(std::vector<unsigned char> *buffer)
{
	mRenderBuffer = buffer;
}

	} // namespace contentJson
} // namespace hermod
/* EOF */
