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
	PositionStack* _top;
	PositionStack* _next;
	Position * _position;
	Move _previousMove;
};
