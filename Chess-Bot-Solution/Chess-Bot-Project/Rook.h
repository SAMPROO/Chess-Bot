#pragma once

#include <list>
#include "ChessPiece.h"
#include "Position.h"

class Rook : virtual public ChessPiece
{
	virtual void getMoves(std::list<Move>& list, Tile* tile, Position* position, int color)
	{
		//nykyiset
		int row = tile->getRow();
		int column = tile->getColumn();

		// oikealle
		for (int i = column + 1; i < 7; i++)
		{
			//mitä ruudussa on (tyhjä tai vastustajan nappula
			ChessPiece* n = position->board[row][i];
			
			if (n == nullptr)
			{
				list.push_back(Move(Tile(row, column), Tile(row, i)));
				continue;
			}

			// onko vastustajan nappula?
			if (n->getColor() != color)
			{
				list.push_back(Move(Tile(row, column), Tile(row, i)));
			}

			break;
		}
	}
}