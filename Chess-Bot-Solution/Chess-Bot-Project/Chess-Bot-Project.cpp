#include <iostream>
#include "UI.h"
#include "Position.h"
using namespace std;


int main()
{
	Position* position = new Position();
	UI* ui = new UI(position);

	while (true) 
	{
		ui->drawBoard();


		std::list<Move> list;

		position->getLegalMoves(list);

		wcout << endl << list.size() << " Moves:\n";
		for (auto s : list)
		{
			Tile originTile = s.getOrigin();
			Tile destinationTile = s.getDestination();
			wcout << "(" << originTile.getColumn() << ", " << originTile.getRow() << ") - ";
			wcout << "(" << destinationTile.getColumn() << ", " << destinationTile.getRow() << ")\n";
		}

		Move * input = &ui->getOpponentMove();

		if (std::find(list.begin(), list.end(), *input) != list.end())
		{
			position->updatePostion(input);
		}	
	}	
}