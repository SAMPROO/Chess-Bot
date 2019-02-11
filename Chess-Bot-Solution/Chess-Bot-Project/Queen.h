#pragma once

#include "ChessPiece.h"

class Queen : virtual public ChessPiece
{
public:

	Queen(std::wstring unicode, int color, int code) : ChessPiece(unicode, color, code) {}

	virtual void getMoves(std::list<Move>& list, Tile* tile, Position* position, int color)
	{
		
	}
};