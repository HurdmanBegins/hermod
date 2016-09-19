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
#ifndef CONTENTHTML_H_HPP
#define CONTENTHTML_H_HPP
#include <vector>
#include "HtmlElement.hpp"

namespace hermod {
	namespace contentHtml {

class HtmlH : public HtmlElement {
public:
	explicit HtmlH(int level);
	void renderHead(void);
	void renderTail(void);
protected:
	int mHeaderLevel;
};

	} // namespace ContentHtml
} // namespace hermod
#endif
