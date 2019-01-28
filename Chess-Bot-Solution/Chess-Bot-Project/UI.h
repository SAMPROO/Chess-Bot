#pragma once

#include "Position.h"
#include "Move.h"

class UI {

public:
	UI(Position* position);
	Position* _position;
	void drawBoard();
	Move getOpponentMove();
};
