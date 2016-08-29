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
#ifndef CONTENTJSON_HPP
#define CONTENTJSON_HPP
#include "Content.hpp"
#include "ContentJson/JsonElement.hpp"

namespace hermod {

namespace contentJson {
class JsonElement;
}

/**
 * @class ContentJson
 * @brief This class id used to handle JSON content
 *
 */
class ContentJson : public Content {
public:
	enum RootType { Array, Boolean, Null, Number, Object, String };
public:
	ContentJson();
	~ContentJson();
	contentJson::JsonElement *root(void);
	void setRoot(contentJson::JsonElement *root);
protected:
	void refresh(void);
private:
	contentJson::JsonElement *mRootElement;
};

} // namespace hermod
#endif
