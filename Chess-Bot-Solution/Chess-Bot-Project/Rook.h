#pragma once

#include <list>
#include "ChessPiece.h"
#include "Position.h"

class Rook : virtual public ChessPiece
{
	virtual void getMoves(std::list<Move>& list, Tile* tile, Position* position, int color)
	{
		int row = tile->getRow();
		int column = tile->getColumn();

		Tile origin = Tile(row, column);

		// Right
		for (int i = column + 1; i < 7; i++)
		{
			ChessPiece* n = position->board[row][i];
			
			if (n == nullptr)
			{
				list.push_back(Move(origin, Tile(row, i)));
				continue;
			}

			if (n->getColor() != color)
			{
				list.push_back(Move(origin, Tile(row, i)));
			}

			break;
		}

		// Left
		for (int i = column - 1; i >= 0; i--)
		{
			ChessPiece* n = position->board[row][i];

			if (n == nullptr)
			{
				list.push_back(Move(origin, Tile(row, i)));
				continue;
			}

			if (n->getColor() != color)
			{
				list.push_back(Move(origin, Tile(row, i)));
			}

			break;
		}

		// Up
		for (int i = row + 1; i < 7; i++)
		{
			ChessPiece* n = position->board[i][column];

			if (n == nullptr)
			{
				list.push_back(Move(origin, Tile(i, column)));
				continue;
			}

			if (n->getColor() != color)
			{
				list.push_back(Move(origin, Tile(i, column)));
			}

			break;
		}

		// Down
		for (int i = row - 1; i >= 0; i--)
		{
			ChessPiece* n = position->board[i][column];

			if (n == nullptr)
			{
				list.push_back(Move(origin, Tile(i, column)));
				continue;
			}

			if (n->getColor() != color)
			{
				list.push_back(Move(origin, Tile(i, column)));
			}

			break;
		}
	}
};