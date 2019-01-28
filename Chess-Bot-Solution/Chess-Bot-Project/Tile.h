#pragma once

class Tile {
public:
	Tile(int, int);
	Tile() {}
	int getRow();
	int getColumn();
private:
	int _column;
	int _row;
};
