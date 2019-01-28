#pragma once

#include "Tile.h"

class Move {
public:
	Move(Tile, Tile);
	Move() {}
	Move(bool shortRook, bool longRook); // Castling
	Tile getOrigin();
	Tile getDestination();
	bool isShortRook();
	bool isLongRook();
private:
	Tile _origin;
	Tile _destination;
	int _upgradeTo = 0;
	bool _shortRook;
	bool _longRook;
};
