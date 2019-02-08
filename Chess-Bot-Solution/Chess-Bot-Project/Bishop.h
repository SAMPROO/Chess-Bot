#pragma once

#include <list>
#include "ChessPiece.h"
#include "Position.h"

class Bishop : virtual public ChessPiece
{
	virtual void getMoves(std::list<Move>& list, Tile* tile, Position* position, int color)
	{
		int row = tile->getRow();
		int column = tile->getColumn();

		Tile origin = Tile(row, column);

		// Up Right
		for (int i = 1; i < 7; i++)
		{
			int new_row = row + i;
			int new_column = column + i;

			if (new_row > 7 || new_column > 7)
				break;

			ChessPiece* n = position->board[new_row][new_column];

			//Is new location empty?
			if (n == nullptr)
			{
				list.push_back(Move(origin, Tile(new_row, new_column)));
				continue;
			}

			// Is location occupied by opponent?
			if (n->getColor() != color)
			{
				list.push_back(Move(origin, Tile(new_row, new_column)));
			}

			break;
		}

		// Up Left
		for (int i = 1; i < 7; i++)
		{
			int new_row = row + i;
			int new_column = column - i;

			if (new_row > 7 || new_column > 7)
				break;

			ChessPiece* n = position->board[new_row][new_column];

			//Is new location empty?
			if (n == nullptr)
			{
				list.push_back(Move(origin, Tile(new_row, new_column)));
				continue;
			}

			// Is location occupied by opponent?
			if (n->getColor() != color)
			{
				list.push_back(Move(origin, Tile(new_row, new_column)));
			}

			break;
		}

		// Down Right
		for (int i = 1; i < 7; i++)
		{
			int new_row = row - i;
			int new_column = column + i;

			if (new_row < 0 || new_column < 0)
				break;

			ChessPiece* n = position->board[new_row][new_column];

			//Is new location empty?
			if (n == nullptr)
			{
				list.push_back(Move(origin, Tile(new_row, new_column)));
				continue;
			}

			// Is location occupied by opponent?
			if (n->getColor() != color)
			{
				list.push_back(Move(origin, Tile(new_row, new_column)));
			}

			break;
		}

		// Down Left
		for (int i = 1; i < 7; i++)
		{
			int new_row = row - i;
			int new_column = column - i;

			if (new_row < 0 || new_column < 0)
				break;

			ChessPiece* n = position->board[new_row][new_column];

			//Is new location empty?
			if (n == nullptr)
			{
				list.push_back(Move(origin, Tile(new_row, new_column)));
				continue;
			}

			// Is location occupied by opponent?
			if (n->getColor() != color)
			{
				list.push_back(Move(origin, Tile(new_row, new_column)));
			}

			break;
		}
	}
};