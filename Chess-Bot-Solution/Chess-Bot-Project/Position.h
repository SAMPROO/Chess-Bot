#pragma once
#include "ChessPiece.h"

class Position {

public:
	//Constructor sets the starting position on the board
	Position();
	ChessPiece * board[8][8];
};
