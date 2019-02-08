#pragma once

#include "ChessPiece.h"

class Queen : virtual public ChessPiece
{
	virtual void getMoves(std::list<Move>& list, Tile* tile, Position* position, int color)
	{
		
	}
};