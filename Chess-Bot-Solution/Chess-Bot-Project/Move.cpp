#include "Move.h"

Move::Move(Tile origin, Tile destination) {
	_origin = origin;
	_destination = destination;
	_shortRook = false;
	_longRook = false;
}

Move::Move(bool shortRook, bool longRook) {
	_shortRook = shortRook;
	_longRook = longRook;
}

Tile Move::getOrigin() {
	return _origin;
}

Tile Move::getDestination() {
	return _destination;
}

bool Move::isShortRook() {
	return _shortRook;
}

bool Move::isLongRook() {
	return _longRook;
}

