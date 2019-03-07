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

MoveStack::MoveStack() {
	_top = NULL;
}

MoveStack::~MoveStack() {
	while (!isEmpty())
		pop();
}

void MoveStack::push(Move move) 
{
	MoveStack *temp = new MoveStack();
	temp->_move = move;

	for (int i = 0; i < 6; i++) 
		temp->castlingBools[i] = castlingBools[i];

	temp->_next = _top;
	_top = temp;
}

void MoveStack::pop() 
{
	if (!isEmpty())
	{
		MoveStack * oldtop = _top;
		_top = _top->_next;
		delete oldtop;
	}
}

bool MoveStack::isEmpty()
{
	return (_top == NULL);
}