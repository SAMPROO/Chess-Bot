#pragma once
#include "ChessPiece.h"
#include "Move.h"

class Position {

public:
	//Constructor sets the starting position on the board
	Position();
	ChessPiece * board[8][8];

	static ChessPiece *wKing, *wQueen, *wRook, *wBishop, *wHorse, *wPawn;	// Valkeat nappulat.
	static ChessPiece *bKing, *bQueen, *bRook, *bBishop, *bHorse, *bPawn;	// Mustat nappulat.

	void updatePostion(Move* move);
	int getTurn();
	void setTurn(int color);

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


	Tile findKing(int color);
	bool isTileThreatened(Tile tile, int color);

private:
	int _turn = 0;
	bool _hasWhiteKingMoved = 0;
	bool _hasBlackKingMoved = 0;
	bool _hasWhiteQueenRookMoved = 0;
	bool _hasWhiteKingRookMoved = 0;
	bool _hasBlackQueenRookMoved = 0;
	bool _hasBlackKingRookMoved = 0;

};
