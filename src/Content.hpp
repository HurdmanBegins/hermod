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
#ifndef CONTENT_HPP
#define CONTENT_HPP
#include <vector>

namespace hermod {

/**
 * @class Content
 * @brief This class define a generic data buffer used to hold content
 *
 */
class Content {
public:
	Content();
	virtual ~Content();
	virtual void append(const std::string &str);
	const char *getCBuffer(void);
	int   size(void);
protected:
	std::vector<unsigned char> mBuffer;
};

} // namespace hermod
#endif
