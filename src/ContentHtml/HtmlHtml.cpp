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
#include "HtmlHtml.hpp"

namespace hermod {
	namespace contentHtml {

HtmlHtml::HtmlHtml()
{
}

void HtmlHtml::renderHead(void)
{
	std::string str;
	str  = "<!DOCTYPE HTML>";
	str += "<html>";
	str += "<body>";
	
	renderAppend(str);
}

void HtmlHtml::renderTail(void)
{
	std::string str;
	str  = "</body>";
	str += "</html>";
	
	renderAppend(str);
}

	} // namespace ContentHtml
} // namespace hermod
/* EOF */
