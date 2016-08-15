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
#ifndef CONFIG_H
#define CONFIG_H

#ifndef INSTALL
#define INSTALL "/usr/local"
#endif

#ifndef DEF_CFG_FILE
#define DEF_CFG_FILE INSTALL "/etc/hermod/main.cfg"
#endif

#ifndef DEF_DIR_ROOT
#define DEF_DIR_ROOT  "/var/hermod/"
#endif

#ifndef DEF_DIR_SESS
#define DEF_DIR_SESS  "/tmp/"
#endif

#ifndef DEF_LOG_FILE
#define DEF_LOG_FILE  "/var/log/hermod.log"
#endif

#ifndef DEF_DIR_PLUGINS
#define DEF_DIR_PLUGINS INSTALL "/lib/hermod/"
#endif

#endif
/* EOF */
