#pragma once
#include "ChessPiece.h"
#include "MoveStack.h"
#include "MinMaxReturn.h"
#include "PieceSquareValues.h"

using namespace std;

//class MoveStack;

class Position {

public:
	//Constructor sets the starting position on the board
	Position(MoveStack * moveStack);
	ChessPiece * board[8][8];

	static ChessPiece *wKing, *wQueen, *wRook, *wBishop, *wHorse, *wPawn;	// Valkeat nappulat.
	static ChessPiece *bKing, *bQueen, *bRook, *bBishop, *bHorse, *bPawn;	// Mustat nappulat.

	Tile* _whiteKing;
	Tile* _blackKing;

	void updatePosition(Move* move, bool realMove = true);
	void undoMove();

	int getTurn();
	void changeTurn();

	bool getKingMoved(int color);
	bool getShortRookMoved(int color);
	bool getLongRookMoved(int color);

	void setKingMoved();
	void setShortRookMoved();
	void setLongRookMoved();

	void getLegalMoves(std::list<Move>& moves, int turn);
	void getRawMoves(std::list<Move>& moves, int turn);

	void isCheck(std::list<Move>& moves, int turn);

	void addCastling(std::list<Move>& moves, int turn);
	void addEnPassant(std::list<Move>& moves, int turn);
	

	bool isTileThreatened(Tile tile, int color);

	MoveStack * _moveStack;

	double endResult(int turn);
	double evaluate(Move currentMove, int turn);
	MinMaxReturn minimax(int depth, double alpha, double beta, int turn, Move currentMove);
	double calculateMaterialValue();
	double calculatePieceTileValue(Move currentMove, int turn);

	static const PieceTileValue _pieceTileValues;
	
	double inf = numeric_limits<double>::infinity();
};
