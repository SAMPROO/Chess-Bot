#pragma once
#include "ChessPiece.h"
#include "MoveStack.h"

//class MoveStack;

class Position {

public:
	//Constructor sets the starting position on the board
	Position(MoveStack * moveStack);
	ChessPiece * board[8][8];

	static ChessPiece *wKing, *wQueen, *wRook, *wBishop, *wHorse, *wPawn;	// Valkeat nappulat.
	static ChessPiece *bKing, *bQueen, *bRook, *bBishop, *bHorse, *bPawn;	// Mustat nappulat.

	void updatePosition(Move* move);
	void undoMove();

	int getTurn();
	void changeTurn();

	bool getKingMoved(int color);
	bool getShortRookMoved(int color);
	bool getLongRookMoved(int color);

	void setKingMoved();
	void setShortRookMoved();
	void setLongRookMoved();

	//bool getWhiteKingMoved();
	//bool getBlackKingMoved();
	//bool getWhiteQueenRookMoved();
	//bool getWhiteKingRookMoved();
	//bool getBlackQueenRookMoved();
	//bool getBlackKingRookMoved();

	void getLegalMoves(std::list<Move>& list);
	void getRawMoves(std::list<Move>& moves, int color);

	void isCheck(std::list<Move>& moves);
	void addCastling(std::list<Move>& moves);

	bool isTileThreatened(Tile tile, int color);

	MoveStack * _moveStack;

private:
	int _turn = 0;
};
