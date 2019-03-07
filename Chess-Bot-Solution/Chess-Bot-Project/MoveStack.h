#pragma once

#include <iostream>
#include "ChessPiece.h"

class MoveStack {
public:

	MoveStack();
	~MoveStack();

	void push(Move move);

	void pop();

	bool isEmpty();

	bool castlingBools[6] = { 0 };

	Move _move;
	ChessPiece * _capturedPiece = NULL;
	ChessPiece * _upgradedFrom = NULL;

private:
	MoveStack* _top;
	MoveStack* _next;

	//bool _hasWhiteKingMoved = 0;
	//bool _hasBlackKingMoved = 0;
	//bool _hasWhiteQueenRookMoved = 0;
	//bool _hasWhiteKingRookMoved = 0;
	//bool _hasBlackQueenRookMoved = 0;
	//bool _hasBlackKingRookMoved = 0;
};
