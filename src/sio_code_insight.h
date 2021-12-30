#pragma once

struct SIOLineInfoRange
{
	const int start_ln;
	const int start_col;
	const int end_ln;
	const int end_col;
};

class SIOPosInfo
{
private:
	int ln = 1;
	int col = 0;

	int update_ln = 1;
	int update_col = 0;

	int capture_start_ln = 0;
	int capture_start_col = 0;
protected:
	void reset_pos_info();
	void set_pos_info(int ln, int col);

	void update_ln_pos();
	void update_col_pos();

	void apply_update();

	void start_capture();
	SIOLineInfoRange stop_capture();
public:
	SIOPosInfo() {}
	SIOPosInfo(int ln, int col) : ln(ln), col(col) {}

	const int get_ln_pos();
	const int get_col_pos();
};