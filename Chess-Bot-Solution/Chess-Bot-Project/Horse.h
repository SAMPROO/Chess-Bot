#pragma once

#include "ChessPiece.h"

class Horse : virtual public ChessPiece
{
	virtual void getMoves(std::list<Move>& list, Tile* tile, Position* position, int color)
	{
		//Current location
		int row = tile->getRow();
		int column = tile->getColumn();

		//Horse possible moves
		int moves[8][2] = { 
			{ -2, -1 },
			{ -2, +1 },
			{ +2, -1 },
			{ +2, +1 },
			{ -1, -2 },
			{ -1, +2 },
			{ +1, -2 }, 
			{ +1, +2 } };

		//Loop through moves
		for (int i = 0; i < 7; i++)
		{
			//Possible new location
			int new_row = row + moves[i][0];
			int new_column = column + moves[i][1];

			//If new move out of bounds then break
			if (new_row > 7 || new_row < 0 || new_column > 7 || new_column < 0)
			{
				break;
			}

			ChessPiece* n = position->board[new_row][new_column];

			//Is new location empty?
			if (n == nullptr)
			{
				//Add new location to move list
				list.push_back(Move(Tile(row, column), Tile(new_row, new_column)));
				continue;
			}

			// Is location occupied by opponent?
			if (n->getColor() != color)
			{
				//Add new location to move list
				list.push_back(Move(Tile(row, column), Tile(new_row, new_column)));
			}

			break;

		}


		
	}
};