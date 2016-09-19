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
#ifndef CONTENTHTML_ELEMENT_HPP
#define CONTENTHTML_ELEMENT_HPP
#include <string>
#include <vector>

namespace hermod {
	namespace contentHtml {

/**
 * @class HtmlElement
 * @brief This class may be used to define a generic element of an Html content
 *
 */
class HtmlElement {
public:
	HtmlElement();
	virtual ~HtmlElement();
	virtual void add(HtmlElement *element);
	virtual void add(const std::string &str);
	virtual void render(void);
	void setRenderBuffer(std::vector<unsigned char> *buffer);
protected:
	void renderAppend(const std::string &str);
	virtual void renderHead(void);
	virtual void renderBody(void);
	virtual void renderTail(void);
protected:
	std::vector<HtmlElement *>  mChildren;
	std::vector<unsigned char> *mRenderBuffer;
	std::string mText;
};

	} // namespace ContentHtml
} // namespace hermod
#endif
