#pragma once

#include "Tile.h"

class Move {
public:
	Move(Tile, Tile);
	Move() {}
	Move(bool shortRook, bool longRook); // Castling
	bool operator ==(const Move& rhs) const;
	Tile getOrigin();
	Tile getDestination();
	bool isShortRook();
	bool isLongRook();
private:
	Tile _origin;
	Tile _destination;
	int _upgradeTo = 0;
	bool _shortRook = false;
	bool _longRook = false;
};
