#pragma once

class Tile {
public:
	Tile(int row, int column);
	Tile() {}
	bool operator != (const Tile& rhs) const;
	int getRow();
	int getColumn();
private:
	int _column;
	int _row;
};
