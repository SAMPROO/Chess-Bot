#include "Position.h"
#include "Rook.h"
#include "Horse.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"

ChessPiece* Position::wRook = new Rook(L"\u2656", 0, WR);
ChessPiece* Position::wHorse = new Horse(L"\u2658", 0, WH);
ChessPiece* Position::wBishop = new Bishop(L"\u2657", 0, WB);
ChessPiece* Position::wKing = new King(L"\u2654", 0, WK);
ChessPiece* Position::wQueen = new Queen(L"\u2655", 0, WQ);
ChessPiece* Position::wPawn = new Pawn(L"\u2659", 0, WP);
			
ChessPiece* Position::bRook = new Rook(L"\u265C", 1, BR);
ChessPiece* Position::bHorse = new Horse(L"\u265E", 1, BH);
ChessPiece* Position::bBishop = new Bishop(L"\u265D", 1, BB);
ChessPiece* Position::bKing = new King(L"\u265A", 1, BK);
ChessPiece* Position::bQueen = new Queen(L"\u265B", 1, BQ);
ChessPiece* Position::bPawn = new Pawn(L"\u265F", 1, BP);

Position::Position() {

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			board[i][j] = NULL;

	// Initialization of white pieces 
	board[0][0] = wRook;
	//board[1][0] = wHorse;
	//board[2][0] = wBishop;
	board[3][0] = wKing;
	//board[4][0] = wQueen;
	//board[5][0] = wBishop;
	//board[6][0] = wHorse;
	board[7][0] = wRook;

	//board[4][4] = wPawn;

	//Initialize pawns
	for (int i = 0; i < 8; i++)
	{
		board[i][1] = wPawn;
		board[i][6] = bPawn;
	}

	board[0][7] = bRook;
	//board[1][7] = bHorse;
	//board[2][7] = bBishop;
	board[3][7] = bKing;
	//board[4][7] = bQueen;
	//board[5][7] = bBishop;
	//board[6][7] = bHorse;
	board[7][7] = bRook;
}

void Position::updatePostion(Move* move)
{
	int end = _turn ? 7 : 0;

	// Short Rook
	if (move->isShortRook()) {
		board[6][end] = board[4][end]; // King to new position
		board[4][end] = NULL; // Clear old position
		board[5][end] = board[7][end]; // Rook to new position
		board[7][end] = NULL; // Clear old position
	}
	// Long Rook
	else if (move->isLongRook()) {
		board[2][end] = board[4][end]; // King to new position
		board[4][end] = NULL; // Clear old position
		board[3][end] = board[0][end]; // Rook to new position
		board[0][end] = NULL; // Clear old position
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

		ChessPiece * chessPiece = board[originColumn][originRow];

		if (chessPiece != NULL)
		{
			if (_turn)
			{
				switch (chessPiece->getCode())
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
				switch (chessPiece->getCode())
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
		}

		board[destinationColumn][destinationRow] = chessPiece;
		board[originColumn][originRow] = NULL;
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

bool Position::getKingMoved(int color)
{
	return color ? _hasWhiteKingMoved : _hasBlackKingMoved;
}

bool Position::getShortRookMoved(int color)
{
	return color ? _hasWhiteKingRookMoved : _hasBlackKingRookMoved;
}

bool Position::getLongRookMoved(int color)
{
	return color ? _hasWhiteQueenRookMoved : _hasBlackQueenRookMoved;
}

//bool Position::getWhiteKingMoved()
//{
//	return _hasWhiteKingMoved;
//}
//
//bool Position::getBlackKingMoved()
//{
//	return _hasBlackKingMoved;
//}
//
//bool Position::getWhiteQueenRookMoved()
//{
//	return _hasWhiteQueenRookMoved;
//}
//
//bool Position::getWhiteKingRookMoved()
//{
//	return _hasWhiteKingRookMoved;
//}
//
//bool Position::getBlackQueenRookMoved()
//{
//	return _hasBlackQueenRookMoved;
//}
//
//bool Position::getBlackKingRookMoved()
//{
//	return _hasBlackKingRookMoved;
//}

void Position::getLegalMoves(std::list<Move>& moves)
{
	getRawMoves(moves, _turn);
	addCastling(moves);
	checkKingCheck(moves);
}

void Position::getRawMoves(std::list<Move>& moves, int color)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			ChessPiece * chessPiece = board[j][i];

			if (chessPiece != NULL && chessPiece->getColor() == color)
			{
				chessPiece->getMoves(moves, &Tile(i, j), this, color);
			}
		}
	}
}

void Position::checkKingCheck(std::list<Move>& moves)
{
	Tile king = findKing(_turn);

	std::list<Move> safeMoves;

	for (Move move : moves)
	{
		Position newPosition = *this;

		newPosition.updatePostion(&move);

		Tile kingTile = move.getOrigin() == king ? move.getDestination() : king;

		if (newPosition.isTileThreatened(kingTile, !_turn) == false)
		{
			safeMoves.push_back(move);
		}
	}

	moves = safeMoves;
}

Tile Position::findKing(int color)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			ChessPiece * chessPiece = board[i][j];

			if (chessPiece != NULL && (chessPiece->getCode() == WK || chessPiece->getCode() == BK) && chessPiece->getColor() == _turn)
			{
				return Tile(j, i);
			}
		}
	}
}

void Position::addCastling(std::list<Move>& moves)
{
	//// Linnoituksien huomioiminen
	//// 1. Kuningas ei saa olla liikkunut
	//// 2. Torni ei saa olla liikkunut
	//// 3. Kuningas ei saa olla shakattuna
	//// 4. Ruutujen pit‰‰ olla tyhj‰t
	//// 5. Ruudut eiv‰t saa olla uhattuja

	int row = _turn ? 0 : 7;

	if (getKingMoved(_turn) == false && isTileThreatened(Tile(4, row), !_turn) == false)
	{
		// short rook
		if (getShortRookMoved(_turn) == false			
			&& board[5][row] == NULL 
			&& board[6][row] == NULL
			&& isTileThreatened(Tile(5, row), !_turn) == false
			&& isTileThreatened(Tile(6, row), !_turn) == false)

			moves.push_back(Move(true, false));		

		// long rook
		if (getLongRookMoved(_turn) == false
			&& board[3][row] == NULL 
			&& board[2][row] == NULL
			&& isTileThreatened(Tile(3, row), !_turn) == false
			&& isTileThreatened(Tile(2, row), !_turn) == false)
			
			moves.push_back(Move(false, true));
	}
	
}

bool Position::isTileThreatened(Tile tile, int enemyColor)
{
	std::list<Move> enemyMoves;
	getRawMoves(enemyMoves, enemyColor);

	for (Move move : enemyMoves)
	{
		Tile origin = move.getOrigin();
		ChessPiece * chessPiece = board[origin.getColumn()][origin.getRow()];

		if (chessPiece != NULL && move.getDestination() == tile)
		{
			if (chessPiece->getCode() == WP || chessPiece->getCode() == BP)
			{
				return origin.getColumn() != tile.getColumn();
			}

			return true;
		}
	}

	return false;
}
