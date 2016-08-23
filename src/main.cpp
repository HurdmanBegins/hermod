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
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <string>
#include <signal.h>
#include "App.hpp"
#include "Config.hpp"

static void config(int argc, char **argv);
static void signal_handler(int sig);

int main(int argc, char **argv)
{
	struct sigaction sa;

	config(argc, argv);

	App app;

	// Initialise signal handler
	sigemptyset(&sa.sa_mask);
	sa.sa_flags   = 0;
	sa.sa_handler = signal_handler;
	// Install signal handler
	sigaction(SIGINT, &sa, NULL);

	app.init();
	app.exec();

	return(0);
}

static void config(int argc, char **argv)
{
	std::string cfgFilename(DEF_CFG_FILE);

	try {
		for (int i = 1; i < argc; i++)
		{
			bool hasMore = ( (i + 1) < argc);
			if (std::string("-c").compare(argv[i]) == 0)
			{
				if ( ! hasMore)
					throw runtime_error("Missing argument for -c");
				i++;
				cfgFilename = argv[i];
			}
		}
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		exit(-1);
	}

	Config *cfg = Config::getInstance();
	// 
	try {
		cfg->load(cfgFilename);
	} catch (std::exception &e) {
		std::cerr << "Failed to load config file " << cfgFilename << std::endl;
	}
	// Insert default config
	if ( cfg->get("global", "root_src").empty() )
		cfg->set("global",  "root_src", DEF_DIR_ROOT);
	if ( cfg->get("global", "path_session").empty() )
		cfg->set("global",  "path_session", DEF_DIR_SESS);
	if ( cfg->get("global", "log_file").empty() )
		cfg->set("global", "log_file", DEF_LOG_FILE);
	if ( cfg->get("global", "session_mode").empty() )
		cfg->set("global", "session_mode", "cookie");
	if ( cfg->get("plugins", "directory").empty() )
		cfg->set("plugins", "directory", DEF_DIR_PLUGINS);
}

static void signal_handler(int sig)
{
	if (sig == SIGINT)
		App::sigInt();
}
