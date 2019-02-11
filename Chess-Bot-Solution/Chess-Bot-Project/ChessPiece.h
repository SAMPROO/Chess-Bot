#pragma once

#include <string>
#include <list>
#include "Move.h"
// #include "Position.h"

class Position;

// constants for chess pieces
enum
{
	WR, WH, WB, WQ, WK, WP,
	BR, BH, BB, BQ, BK, BP
};

class ChessPiece {

private:
	std::wstring _unicode;
	int _color = 0; // white = 0, black = 1
	int _code; // enum
public:
	ChessPiece(std::wstring, int, int);
	void setCode(int);
	int getCode();
	void setUnicode(std::wstring);
	std::wstring getUnicode();
	void setColor(int);
	int getColor();

	virtual void getMoves(
		std::list<Move>& list,
		Tile* tile,
		Position* position,
		int color
	) = 0;
};



