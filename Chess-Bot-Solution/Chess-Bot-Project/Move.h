#pragma once
#include "Tile.h"

class Move {
public:
	Move(Tile, Tile, bool enPassant = false, bool promoted = false);
	Move() {}
	Move(bool shortRook, bool longRook); // Castling
	bool operator ==(const Move& rhs) const;
	Tile getOrigin();
	Tile getDestination();
	bool isShortRook();
	bool isLongRook();
	bool isEnPassant();
	bool isPromoted();

private:
	Tile _origin;
	Tile _destination;
	bool _shortRook = false;
	bool _longRook = false;
	bool _enPassant;
	bool _promoted;
};
