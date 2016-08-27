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
#include "HtmlH.hpp"

namespace hermod {
	namespace contentHtml {

HtmlH::HtmlH(int level)
{
	mHeaderLevel = level;
}

void HtmlH::renderHead(void)
{
	std::ostringstream ss;
	ss << "<h" << mHeaderLevel << ">";
	
	renderAppend(ss.str());
}

void HtmlH::renderTail(void)
{
	std::ostringstream ss;
	ss << "</h" << mHeaderLevel << ">";
	
	renderAppend(ss.str());
}

	} // namespace ContentHtml
} // namespace hermod
/* EOF */
