#pragma once

#include "Position.h"

using namespace std;

class UI {

public:
	UI(Position* position);
	Position* _position;
	void drawBoard();
	Move getOpponentMove(string inputOpponentMove);
};
