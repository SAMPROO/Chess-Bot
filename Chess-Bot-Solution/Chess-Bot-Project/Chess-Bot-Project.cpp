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

		wcout << "\nColor: " << (position->getTurn() ? "Black" : "White") 
			<< endl << list.size() << " Moves:\n";
		for (auto s : list)
		{
			if (s.isShortRook())
			{
				wcout << "0-0\n";
			}
			else if (s.isLongRook())
			{
				wcout << "0-0-0\n";
			}
			else
			{
				Tile originTile = s.getOrigin();
				Tile destinationTile = s.getDestination();
				wcout << "(" << originTile.getColumn() << ", " << originTile.getRow() << ") - ";
				wcout << "(" << destinationTile.getColumn() << ", " << destinationTile.getRow() << ")\n";
			}			
		}

		Move * input;

		do {
			input = &ui->getOpponentMove();
		} while (std::find(list.begin(), list.end(), *input) == list.end());

		position->updatePostion(input);
	}
}
