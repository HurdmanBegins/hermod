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
#ifndef CONTENTJSON_ELEMENT_HPP
#define CONTENTJSON_ELEMENT_HPP
#include <string>
#include <vector>

namespace hermod {
	namespace contentJson {

/**
 * @class JsonElement
 * @brief This class may be used to define a generic element of a JSON content
 *
 */
class JsonElement {
public:
	JsonElement();
	virtual ~JsonElement();
	std::string getName(void);
	void setName(const std::string &name);
	void setRenderBuffer(std::vector<unsigned char> *buffer);
public:
	virtual void render(void);
protected:
	void renderAppend(const std::string &str);
	virtual void renderHead(void);
	virtual void renderBody(void);
	virtual void renderTail(void);
protected:
	std::string mName;
	std::vector<unsigned char> *mRenderBuffer;
};

	} // namespace ContentJson
} // namespace hermod
#endif
