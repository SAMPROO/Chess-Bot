#pragma once

#include <string>

// Vakioarvot nappulatyypeille.
enum
{
	WR, WH, WB, WQ, WK, WP,
	BR, BH, BB, BQ, BK, BP
};

class ChessPiece {

private:
	std::wstring _unicode;
	int _color; // valkea = 0, musta = 1
	int _code; // VT, VR, MT tms.
public:
	ChessPiece(std::wstring, int, int);
	ChessPiece() {};
	void setCode(int);
	int getCode();
	void setUnicode(std::wstring);
	std::wstring getUnicode();
	void setColor(int);
	int getColor();
};


