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
#ifndef MODULECACHE_HPP
#define MODULECACHE_HPP
#include "Module.hpp"
#include <vector>

namespace hermod {

/**
 * @class ModuleCache
 * @brief This class is used to load/unload additional modules
 *
 */
class ModuleCache
{
public:
	ModuleCache();
	~ModuleCache();
	void   clear(void);
	Module *load(const std::string &name);
	void  unload(int );
private:
	std::vector<Module *> mModules;
};

} // namespace hermod
#endif
