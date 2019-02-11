#include "Position.h"
#include "Rook.h"
#include "Horse.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"


Position::Position() {

	// Initialization of white pieces 
	board[0][0] = new Rook(L"\u2656", 0, WR);
	board[1][0] = new Horse(L"\u2658", 0, WH);
	board[2][0] = new Bishop(L"\u2657", 0, WB);
	board[3][0] = new King(L"\u2654", 0, WK);
	board[4][0] = new Queen(L"\u2655", 0, WQ);
	board[5][0] = new Bishop(L"\u2657", 0, WB);
	board[6][0] = new Horse(L"\u2658", 0, WH);
	board[7][0] = new Rook(L"\u2656", 0, WR);

	//Initialize pawns
	for (int i = 0; i < 8; i++)
	{
		board[i][1] = new Pawn(L"\u2659", 0, WP);
		board[i][6] = new Pawn(L"\u265F", 1, BP);

	}

	// Initialization of empty positions 
	for (int i = 0; i < 8; i++)
	{
		for (int j = 2; j < 6; j++)
		{
			board[i][j] = 0;
		}
	}

	board[0][7] = new Rook(L"\u265C", 1, BR);
	board[1][7] = new Horse(L"\u265E", 1, BH);
	board[2][7] = new Bishop(L"\u265D", 1, BB);
	board[3][7] = new King(L"\u265A", 1, BK);
	board[4][7] = new Queen(L"\u265B", 1, BQ);
	board[5][7] = new Bishop(L"\u265D", 1, BB);
	board[6][7] = new Horse(L"\u265E", 1, BH);
	board[7][7] = new Rook(L"\u265C", 1, BR);
}

void Position::updatePostion(Move* move)
{
	int end = _turn ? 7 : 0;

	// Short Rook
	if (move->isShortRook()) {
		board[6][end] = board[4][end]; // King to new position
		board[4][end] = 0; // Clear old position
		board[5][end] = board[7][end]; // Rook to new position
		board[7][end] = 0; // Clear old position
	}
	// Long Rook
	else if (move->isLongRook()) {
		board[2][end] = board[4][end]; // King to new position
		board[4][end] = 0; // Clear old position
		board[3][end] = board[0][end]; // Rook to new position
		board[0][end] = 0; // Clear old position
	}
	// Normal move
	else 
	{
		Tile tileOrigin = move->getOrigin();
		Tile tileDestination = move->getDestination();

		int destinationRow = tileDestination.getRow();
		int destinationColumn = tileDestination.getColumn();

		int originRow = tileOrigin.getRow();
		int originColumn = tileOrigin.getColumn();

		if (_turn)
		{
			switch (board[originColumn][originRow]->getCode())
			{
			case BR:
				if (originColumn)
				{
					_hasBlackQueenRookMoved = true;
				}
				else
				{
					_hasBlackKingRookMoved = true;
				}
				break;
			case BK:
				_hasBlackKingMoved = true;
				break;
			}
			setTurn(0);
		}
		else
		{
			switch (board[originColumn][originRow]->getCode())
			{
			case WR:
				if (originColumn)
				{
					_hasWhiteQueenRookMoved = true;
				}
				else
				{
					_hasWhiteKingRookMoved = true;
				}
				break;
			case WK:
				_hasWhiteKingMoved = true;
				break;
			}
			setTurn(1);
		}

		board[destinationColumn][destinationRow] = board[originColumn][originRow];
		board[originColumn][originRow] = 0;
	}
}

int Position::getTurn()
{
	return _turn;
}

void Position::setTurn(int color)
{
	_turn = color;
}

bool Position::getWhiteKingMoved()
{
	return _hasWhiteKingMoved;
}

bool Position::getBlackKingMoved()
{
	return _hasBlackKingMoved;
}

bool Position::getWhiteQueenRookMoved()
{
	return _hasWhiteQueenRookMoved;
}

bool Position::getWhiteKingRookMoved()
{
	return _hasWhiteKingRookMoved;
}

bool Position::getBlackQueenRookMoved()
{
	return _hasBlackQueenRookMoved;
}

bool Position::getBlackKingRookMoved()
{
	return _hasBlackKingRookMoved;
}

void Position::getLegalMoves(std::list<Move>& list)
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			ChessPiece * chessPiece = board[j][i];

			if (chessPiece != NULL && chessPiece->getColor() == _turn)
			{
				chessPiece->getMoves(list, new Tile(i, j), this, _turn);
			}
		}
	}
}

void Position::getLegalMovesFromOrigin(std::list<Move>& list, Tile origin)
{
	ChessPiece * chessPiece = board[origin.getRow()][origin.getColumn()];

	if (chessPiece != NULL && chessPiece->getColor() == _turn)
	{
		chessPiece->getMoves(list, &origin, this, _turn);
	}
}
