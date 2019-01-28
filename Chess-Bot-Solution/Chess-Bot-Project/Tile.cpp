#include "Tile.h"

Tile::Tile(int row, int column) {
	_row = row;
	_column = column;
}

int Tile::getRow() {
	return _row;
}

int Tile::getColumn() {
	return _column;
}