#pragma once

#include "ChessPiece.h"

class Pawn : virtual public ChessPiece
{
	bool hasNotMoved = true;

	virtual void getMoves(std::list<Move>& list, Tile* tile, Position* position, int color)
	{
		//Current location
		int row = tile->getRow();
		int column = tile->getColumn();

		if (hasNotMoved)
		{
			list.push_back(Move(&tile, Tile(row, column)));
		}
	}
};