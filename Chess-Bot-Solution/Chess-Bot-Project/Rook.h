#pragma once

#include <list>
#include "ChessPiece.h"
#include "Position.h"

class Rook : virtual public ChessPiece
{
	virtual void getMoves(
		std::list<Move>& list,
		Tile* tile,
		Position* position,
		int color
	)
	{
		//nykyiset
		// oikealle
			//uudet
			//mitä ruudussa on (tyhjä tai vastustajan nappula
	}
}