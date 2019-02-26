#pragma once

#include "Position.h"

class King : public ChessPiece
{

public:

	King(std::wstring unicode, int color, int code) : ChessPiece(unicode, color, code) {}

	//King possible moves
	int moves[8][2] = {
		{ -1, -1 },
		{ -1, 1 },
		{ -1, 0 },
		{ 1, -1 },
		{ 1, 1 },
		{ 1, 0 },
		{ 0, 1 },
		{ 0, -1 } 
	};

	virtual void getMoves(std::list<Move>& list, Tile* tile, Position* position, int color)
	{
		//Current location
		int row = tile->getRow();
		int column = tile->getColumn();

		//Loop through moves
		for (int i = 0; i < 8; i++)
		{
			//Possible new location
			int new_row = row + moves[i][0];
			int new_column = column + moves[i][1];

			//If new move out of bounds then continue
			if (new_row > 7 || new_row < 0 || new_column > 7 || new_column < 0)
			{
				continue;
			}

			ChessPiece* n = position->board[new_row][new_column];

			//Is new location empty?
			if (n == nullptr)
			{
				//Add new location to move list
				list.push_back(Move(Tile(row, column), Tile(new_row, new_column)));
			}

			// Is location occupied by opponent?
			else if (n->getColor() != color)
			{
				//Add new location to move list
				list.push_back(Move(Tile(row, column), Tile(new_row, new_column)));
			}
		}
	}
};