#pragma once

#include "Tile.h"

class Move {
public:
	Move(Tile, Tile);
	Move() {}
	Move(bool lyhytLinna, bool pitkaLinna); // Poikkeussiirto linnoitusta varten
	Tile getAlkuruutu();
	Tile getLoppuruutu();
	bool onkoLyhytLinna();
	bool onkoPitkälinna();
private:
	Tile alkuRuutu;
	Tile loppuRuutu;
	int miksiKorotetaan = 0;
	bool lyhytLinna;
	bool pitkalinna;
};
