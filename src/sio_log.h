/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <string>
#include <iostream>

#include <sio_code_insight.h>

#include "fmt/core.h"
#include <fmt/color.h>

using namespace std;

// Red console font color
constexpr auto CL_COLOR_ERROR = "\x1B[31m";

// Green console font color
constexpr auto CL_COLOR_SUCCESS = "\x1B[32m";

// Yellow console font color
constexpr auto CL_COLOR_WARNING = "\x1B[33m";

// Blue console font color
constexpr auto CL_COLOR_HINT = "\x1B[34m";

// White console font color
constexpr auto CL_COLOR_DEFAULT = "\x1B[37m";

// Bright red console font color
constexpr auto CL_BRIGHT_COLOR_ERROR = "\x1B[91m";

// Bright green console font color
constexpr auto CL_BRIGHT_COLOR_SUCCESS = "\x1B[92m";

// Bright yellow console font color
constexpr auto CL_BRIGHT_COLOR_WARNING = "\x1B[93m";

// Bright blue console font color
constexpr auto CL_BRIGHT_COLOR_HINT = "\x1B[94m";

// Bright white console font color
constexpr auto CL_BRIGHT_COLOR_DEFAULT = "\x1B[97m";

class SIOLogger
{
protected:
	string section;
public:
	virtual void log_success(string message, int ln = 0, int col = 0) = 0;
	virtual void log_info(string message, int ln = 0, int col = 0) = 0;
	virtual void log_hint(string message, int ln = 0, int col = 0) = 0;
	virtual void log_warn(string message, int ln = 0, int col = 0) = 0;
	virtual void log_error(string message, int ln = 0, int col = 0) = 0;

	void log_success(string message, SIOPosInfo* pos_info);
	void log_info(string message, SIOPosInfo* pos_info);
	void log_hint(string message, SIOPosInfo* pos_info);
	void log_warn(string message, SIOPosInfo* pos_info);
	void log_error(string message, SIOPosInfo* pos_info);

	const string get_section();
	void set_section(const string section);
};

class SIOConsoleLogger : public SIOLogger
{
private:
	void log(ostream& stream, string message, int ln, int col, string color_code = "");
public:
	void log_success(string message, int ln = 0, int col = 0);
	void log_info(string message, int ln = 0, int col = 0);
	void log_hint(string message, int ln = 0, int col = 0);
	void log_warn(string message, int ln = 0, int col = 0);
	void log_error(string message, int ln = 0, int col = 0);
};

class SIOFileLogger : public SIOLogger
{
	//
};