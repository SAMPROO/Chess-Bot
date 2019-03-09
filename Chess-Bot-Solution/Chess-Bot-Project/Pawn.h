#pragma once

#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:

	Pawn(std::wstring unicode, int color, int code) : ChessPiece(unicode, color, code) {}

	virtual void getMoves(std::list<Move>& list, Tile* tile, Position* position, int color)
	{
		//Current location
		int row = tile->getRow();
		int column = tile->getColumn();

		// forward +1
		int delta = color ? -1 : 1;

		int new_row = row + delta;

		if (color ? new_row < 0 : new_row > 7)
			return;

		//Is new location empty?
		if (position->board[column][new_row] == nullptr)
		{
			//Add new location to move list
			list.push_back(Move(*tile, Tile(new_row, column), false, new_row == 7 || new_row == 0));

			// forward +2
			if (row == (color ? 6 : 1))
			{
				//Is new location empty?
				if (position->board[column][new_row + delta] == nullptr)
					//Add new location to move list
					list.push_back(Move(*tile, Tile(new_row + delta, column)));
			}
		}			

		// Attack right
		int new_column = column + 1;

		if (new_column <= 7)
		{
			// Is location occupied by opponent?
			ChessPiece * chessPiece = position->board[new_column][new_row];
			if (chessPiece != NULL && chessPiece->getColor() != color)
				//Add new location to move list
				list.push_back(Move(*tile, Tile(new_row, new_column), false, new_row == 7 || new_row == 0));
		}

		// Attack left
		new_column = column - 1;

		if (new_column >= 0)
		{
			// Is location occupied by opponent?
			ChessPiece * chessPiece = position->board[new_column][new_row];
			if (chessPiece != NULL && chessPiece->getColor() != color)
				//Add new location to move list
				list.push_back(Move(*tile, Tile(new_row, new_column), false, new_row == 7 || new_row == 0));
		}

		
	}
};