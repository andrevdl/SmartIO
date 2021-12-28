#include "sio_log.h"

void SIOLogger::log_success(string message, SIOPosInfo* pos_info)
{
	if (pos_info == nullptr)
	{
		log_success(message);
	}
	else
	{
		log_success(message, pos_info->get_ln_pos(), pos_info->get_col_pos());
	}
}

void SIOLogger::log_info(string message, SIOPosInfo* pos_info)
{
	if (pos_info == nullptr)
	{
		log_info(message);
	}
	else
	{
		log_info(message, pos_info->get_ln_pos(), pos_info->get_col_pos());
	}
}

void SIOLogger::log_hint(string message, SIOPosInfo* pos_info)
{
	if (pos_info == nullptr)
	{
		log_hint(message);
	}
	else
	{
		log_hint(message, pos_info->get_ln_pos(), pos_info->get_col_pos());
	}
}

void SIOLogger::log_warn(string message, SIOPosInfo* pos_info)
{
	if (pos_info == nullptr)
	{
		log_warn(message);
	}
	else
	{
		log_warn(message, pos_info->get_ln_pos(), pos_info->get_col_pos());
	}
}

void SIOLogger::log_error(string message, SIOPosInfo* pos_info)
{
	if (pos_info == nullptr)
	{
		log_error(message);
	}
	else
	{
		log_error(message, pos_info->get_ln_pos(), pos_info->get_col_pos());
	}
}

const string SIOLogger::get_section()
{
	return section;
}

void SIOLogger::set_section(const string section)
{
	this->section = section;
}

void SIOConsoleLogger::log(ostream& stream, string message, int ln, int col, string color_code)
{
	bool lineinfo = ln > 0 && col > 0;
	string _section = section;
	if (_section == "")
	{
		_section = "General";
	}

	if (color_code != "")
	{
		stream << color_code;
	}

	stream << "[" << _section;
	if (lineinfo)
	{
		stream << ": ln " << ln;
		if (col > 0)
		{
			stream << ", col " << ln;
		}
	}

	stream << "] " << message;
	if (color_code != "")
	{
		stream << "\033[0m";
	}
	stream << endl;
}

void SIOConsoleLogger::log_success(string message, int ln, int col)
{
	log(std::cout, message, ln, col, CL_BRIGHT_COLOR_SUCCESS);
}

void SIOConsoleLogger::log_info(string message, int ln, int col)
{
	log(std::cout, message, ln, col);
}

void SIOConsoleLogger::log_hint(string message, int ln, int col)
{
	log(std::cout, message, ln, col, CL_BRIGHT_COLOR_HINT);
}

void SIOConsoleLogger::log_warn(string message, int ln, int col)
{
	log(std::cerr, message, ln, col, CL_BRIGHT_COLOR_WARNING);
}

void SIOConsoleLogger::log_error(string message, int ln, int col)
{
	log(std::cerr, message, ln, col, CL_BRIGHT_COLOR_ERROR);
}

void SIOPosInfo::reset_pos_info()
{
	ln = 1;
	col = 0;
}

void SIOPosInfo::set_pos_info(int ln, int col)
{
	this->ln = ln;
	this->col = col;
}

void SIOPosInfo::update_ln_pos()
{
	++ln;
	col = 0;
}

void SIOPosInfo::update_col_pos()
{
	++col;
}

const int SIOPosInfo::get_ln_pos()
{
	return ln;
}

const int SIOPosInfo::get_col_pos()
{
	return col;
}
