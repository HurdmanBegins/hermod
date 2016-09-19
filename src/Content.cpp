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
#include "Content.hpp"

namespace hermod {

/**
 * @brief Default constructor for a Content object
 *
 */
Content::Content()
{
	mBuffer.clear();
	mValidBuffer = true;
}

/**
 * @brief Default destructor of a Content object
 *
 */
Content::~Content()
{
	// Nothing to do
}

/**
 * @brief Insert a string at the end of data buffer
 *
 * @param str String to add
 */
void Content::append(const std::string &str)
{
	std::copy(str.c_str(),
	          str.c_str()+str.length(),
	          std::back_inserter(mBuffer));
}

/**
 * @brief Get access to the data buffer
 *
 * @return char* Pointer to the internal buffer
 */
const char *Content::getCBuffer(void)
{
	// If the internal buffer is invalid
	if ( ! mValidBuffer)
		// Refresh content
		refresh();
	
	unsigned char *ptr = &mBuffer[0];
	return (char *)ptr;
}

/**
 * @brief Get the size of the data buffer
 *
 * @return integer Number of bytes into data buffer
 */
int Content::size(void)
{
	// If the internal buffer is invalid
	if ( ! mValidBuffer)
		// Refresh content
		refresh();
	
	return mBuffer.size();
}

/**
 * @brief Request a reload/refresh of the internal buffer
 *
 */
void Content::refresh(void)
{
	mValidBuffer = true;
}

} // namespace hermod
/* EOF */
