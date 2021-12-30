#include "sio_code_insight.h"

void SIOPosInfo::reset_pos_info()
{
	ln = 1;
	col = 0;
	update_ln = 1;
	update_col = 0;
}

void SIOPosInfo::set_pos_info(int ln, int col)
{
	this->ln = ln;
	this->col = col;
}

void SIOPosInfo::update_ln_pos()
{
	++update_ln;
	update_col = 0;
}

void SIOPosInfo::update_col_pos()
{
	++update_col;
}

void SIOPosInfo::apply_update()
{
	ln = update_ln;
	col = update_col;
}

void SIOPosInfo::start_capture()
{
	capture_start_ln = ln;
	capture_start_col = col;
}

SIOLineInfoRange SIOPosInfo::stop_capture()
{
	return { capture_start_ln, capture_start_col, ln, col };
}

const int SIOPosInfo::get_ln_pos()
{
	return ln;
}

const int SIOPosInfo::get_col_pos()
{
	return col;
}