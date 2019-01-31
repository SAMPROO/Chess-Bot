#pragma once
#include "ChessPiece.h"
#include "Move.h"

class Position {

public:
	//Constructor sets the starting position on the board
	Position();
	ChessPiece * board[8][8];
	void updatePostion(Move* move);
	int getTurn();
	void setTurn(int color);

	bool getWhiteKingMoved();
	bool getBlackKingMoved();
	bool getWhiteQueenRookMoved();
	bool getWhiteKingRookMoved();
	bool getBlackQueenRookMoved();
	bool getBlackKingRookMoved();


private:
	int _turn;
	bool _hasWhiteKingMoved;
	bool _hasBlackKingMoved;
	bool _hasWhiteQueenRookMoved;
	bool _hasWhiteKingRookMoved;
	bool _hasBlackQueenRookMoved;
	bool _hasBlackKingRookMoved;

};
