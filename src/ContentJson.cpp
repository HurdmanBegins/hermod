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
#include "ContentJson.hpp"
#include "ContentJson/JsonElement.hpp"
#include "Log.hpp"

namespace hermod {

using namespace contentJson;

/**
 * @brief Default constructor
 *
 */
ContentJson::ContentJson()
  : Content()
{
	mValidBuffer = false;
	mRootElement = 0;
}

/**
 * @brief Default destructor
 *
 */
ContentJson::~ContentJson()
{
	if (mRootElement)
	{
		delete mRootElement;
		mRootElement = 0;
	}
}

/**
 * @brief Request a reload/refresh of the internal buffer
 *
 */
void ContentJson::refresh(void)
{
	// Clear the current content of buffer
	mBuffer.clear();
	if (mRootElement)
	{
		// Configure root element to write into internal buffer
		mRootElement->setRenderBuffer(&mBuffer);
		// Request root element to render itself
		mRootElement->render();
		// The internal buffer content is now up-to-date
		mValidBuffer = true;
	}
	else
		Log::warning() << "JSON content refresh without root object" << Log::endl;
}

JsonElement *ContentJson::root(void)
{
	return mRootElement;
}

void ContentJson::setRoot(JsonElement *root)
{
	mRootElement = root;
}

} // namespace hermod
/* EOF */
