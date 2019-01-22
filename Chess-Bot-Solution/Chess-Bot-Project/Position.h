#pragma once
#include "ChessPiece.h"

class Position {

public:
	//Konstruktori luo alkuaseman laudalle
	Position();
	ChessPiece * board[8][8];
};
