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
#include "HtmlElement.hpp"

namespace hermod {
	namespace contentHtml {

/**
 * @brief Default constructor
 *
 */
HtmlElement::HtmlElement()
{
	mChildren.clear();
	mRenderBuffer = 0;
	mText.clear();
}

/**
 * @brief Default destructor
 *
 */
HtmlElement::~HtmlElement()
{
	while( mChildren.size() )
	{
		HtmlElement *e = mChildren.back();
		mChildren.pop_back();
		delete e;
	}
}

/**
 * @brief Insert an HTML element as child of this one
 *
 * @param element Pointer to the element to add into child list
 */
void HtmlElement::add(HtmlElement *element)
{
	mChildren.push_back(element);
}

/**
 * @brief Insert a text string into this element
 *
 * @param text Reference to the string to insert
 */
void HtmlElement::add(const std::string &text)
{
	mText += text;
}

/**
 * @brief Append a string to the output buffer
 *
 * @param str Reference to the string to append
 */
void HtmlElement::renderAppend(const std::string &str)
{
	// Sanity check
	if (mRenderBuffer == 0)
		return;
	
	std::copy(str.c_str(),
	          str.c_str()+str.length(),
	          std::back_inserter(*mRenderBuffer));
}

/**
 * @brief This method produce the HTML (text) code of this object
 *
 */
void HtmlElement::render(void)
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
void HtmlElement::renderHead(void)
{
}

/**
 * @brief Default render for the "body" of this element
 *
 */
void HtmlElement::renderBody(void)
{
	if (mChildren.size())
	{
		std::vector<HtmlElement *>::iterator it;
		for (it = mChildren.begin(); it != mChildren.end(); ++it)
		{
			(*it)->setRenderBuffer(mRenderBuffer);
			(*it)->render();
		}
	}
	else
	{
		renderAppend(mText);
	}
}

/**
 * @brief Default rendre for the "tail" of this element
 *
 */
void HtmlElement::renderTail(void)
{
}

/**
 * @brief Set the output buffer to use for rendering element
 *
 * @param buffer Pointer to the output buffer
 */
void HtmlElement::setRenderBuffer(std::vector<unsigned char> *buffer)
{
	mRenderBuffer = buffer;
}

	} // namespace ContentHtml
} // namespace hermod
/* EOF */
