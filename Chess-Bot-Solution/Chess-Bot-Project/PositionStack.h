#pragma once

#include <iostream>
#include "ChessPiece.h"

class PositionStack {
public:

	PositionStack();
	~PositionStack();

	void push(Position * position, Move previuosMove);

	void pop();
	PositionStack * peak();

	bool isEmpty();

	Move getMove();

private:
	PositionStack* _top = NULL;
	PositionStack* _next = NULL;
	Position * _position = NULL;
	Move _previousMove;
};
