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
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>
#include "Log.hpp"

Log *       Log::mInstance = NULL;
LogCtrl     Log::endl(0);

Log::Log()
{
	mDebug.setLevel(10);
	mInfo.setLevel(20);
}

Log::~Log()
{
}

void Log::destroy(void)
{
	if ( ! mInstance)
		return;
	// Free singleton object
	delete mInstance;
	mInstance = NULL;
}

Log* Log::getInstance()
{
	if ( ! mInstance)
	{
		mInstance = new Log;
	}
	return mInstance;
}

LogStream &Log::debug(void)
{
	// Get the Log singleton object
	Log *l = getInstance();
	// Return the debug LogStream
	return l->mDebug;
}

LogStream &Log::info(void)
{
	// Get the Log singleton object
	Log *l = getInstance();
	// Return the info Logstream
	return l->mInfo;
}

void Log::setFile(const std::string &filename)
{
	// Sanity check
	if (filename.empty())
		throw std::runtime_error("Log: setFile without filename");

	// Get the Log singleton object
	Log *l = getInstance();

	// Close current Log file (if any)
	if ( l->mFile.is_open() )
		l->mFile.close();
	
	// Set new file name
	l->mFilename = filename;

	// Open the target file
	l->mFile.open(l->mFilename.c_str(), std::ios::out | std::ios::trunc);
	if ( ! l->mFile.is_open())
	{
		l->mFilename.clear();
		throw std::runtime_error("Log: setFile could not open the file!");
	}
}

void Log::sync(void)
{
	std::fstream sfile;
	std::ostringstream dat;
	
	Log *l = getInstance();

	dat << l->mInfo.getBuffer();
	if (l->mFile.is_open())
		l->writeToFile(dat.str());
	else
		std::cout << dat.str() << std::flush;
	l->mInfo.clear();
}

void Log::writeToFile(const std::string &msg)
{
	mFile << msg;
	mFile.flush();
}

// --------------------  -------------------- //

LogStream::LogStream()
{
}

LogStream::LogStream(int level)
{
	mLevel = level;
	mBuffer.clear();
}

void LogStream::append  (const std::string &msg)
{
	mLine.append(msg);
}

void LogStream::clear(void)
{
	mBuffer.clear();
}

std::string LogStream::getBuffer(void)
{
	return mBuffer;
}

int  LogStream::getLevel(void)
{
	return(mLevel);
}

void LogStream::setLevel(int level)
{
	mLevel = level;
}

LogStream& operator<<(LogStream &ls, const char msg[])
{
	std::ostringstream oss;
	oss << msg;
	ls.append( oss.str() );
	return ls;
}

LogStream& operator<<(LogStream &ls, const std::string &msg)
{
	std::ostringstream oss;
	oss << msg;
	ls.append( oss.str() );
	return ls;
}

LogStream& operator<<(LogStream &ls, int i)
{
	std::ostringstream oss;
	oss << i;
	ls.append( oss.str() );
	return ls;
}

LogStream& operator<<(LogStream &ls, LogCtrl &ctrl)
{
	// ToDo: decode ctrl value
	(void)ctrl;

	time_t t = time(0);
	struct tm * now = localtime(&t);
	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << now->tm_hour << ":";
	oss << std::setw(2) << std::setfill('0') << now->tm_min  << ":";
	oss << std::setw(2) << std::setfill('0') << now->tm_sec  << " ";
	oss << ls.mLine << "\n";
	ls.mBuffer.append( oss.str() );
	ls.mLine.clear();
	return ls;
}

LogStream& operator<<(LogStream &ls, struct in_addr &in)
{
	std::ostringstream oss;
	unsigned long ip = in.s_addr;
	
	oss << (unsigned long)((ip >>  0) & 0xFF) << ".";
	oss << (unsigned long)((ip >>  8) & 0xFF) << ".";
	oss << (unsigned long)((ip >> 16) & 0xFF) << ".";
	oss << (unsigned long)((ip >> 24) & 0xFF);
	ls.append(oss.str());
	return ls;
}

LogStream& operator<<(LogStream &ls, Session *sess)
{
	std::ostringstream oss;
	oss << sess->getId() << " ";
	ls.append(oss.str());
	return ls;
}
