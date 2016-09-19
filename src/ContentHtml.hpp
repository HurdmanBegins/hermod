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
#ifndef CONTENTHTML_HPP
#define CONTENTHTML_HPP
#include "Content.hpp"
#include "ContentHtml/HtmlElement.hpp"

namespace hermod {

namespace contentHtml {
class HtmlElement;
}

/**
 * @class ContentHtml
 * @brief This class id used to handle HTML content
 *
 */
class ContentHtml : public Content {
public:
	ContentHtml();
	~ContentHtml();
	contentHtml::HtmlElement *root(void);
protected:
	void refresh(void);
private:
	contentHtml::HtmlElement *mRootElement;
};

} // namespace hermod
#endif
