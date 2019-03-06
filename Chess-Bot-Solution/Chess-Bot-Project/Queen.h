#pragma once

#include "ChessPiece.h"
#include "Bishop.h"
#include "Rook.h"

class Queen : public Bishop, public Rook
{
public:

	Queen(std::wstring unicode, int color, int code) : ChessPiece(unicode, color, code), Bishop(unicode, color, code), Rook(unicode, color, code) {}

	virtual void getMoves(std::list<Move>& list, Tile* tile, Position* position, int color)
	{
		Rook::getMoves(list, tile, position, color);
		Bishop::getMoves(list, tile, position, color);
	}
};