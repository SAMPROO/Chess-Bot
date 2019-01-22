#pragma once

#include <string>

// constants for chess pieces
enum
{
	WR, WH, WB, WQ, WK, WP,
	BR, BH, BB, BQ, BK, BP
};

class ChessPiece {

private:
	std::wstring _unicode;
	int _color; // white = 0, black = 1
	int _code; // enum
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


