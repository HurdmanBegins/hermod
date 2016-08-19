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
#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <vector>
#include "RouteTarget.hpp"

class Module;
class Request;

class Router
{
public:
	Router (void);
	~Router();
	RouteTarget *createTarget(Module *module);
	void removeTarget(RouteTarget *target);
	RouteTarget *find(Request *r);
private:
	std::vector<RouteTarget *> mTargets;
};
#endif