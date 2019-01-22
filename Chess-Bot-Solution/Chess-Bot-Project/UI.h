#pragma once

#include "Position.h"

class UI {

public:
	UI(Position* position);
	Position* _position;
	void drawBoard();
};
