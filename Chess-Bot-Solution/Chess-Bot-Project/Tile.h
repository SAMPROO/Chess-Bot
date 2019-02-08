#pragma once

class Tile {
public:
	Tile(int row, int column);
	Tile() {}
	int getRow();
	int getColumn();
private:
	int _column;
	int _row;
};
