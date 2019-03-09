#include <iostream>
#include <algorithm>
#include "UI.h"
#include "Position.h"

using namespace std;


int main()
{
	Position* position = new Position(new MoveStack());
	UI* ui = new UI(position);

	while (1)
	{
		ui->drawBoard();

		std::list<Move> moves;

		position->getLegalMoves(moves);

		wcout << "\nColor: " << (position->getTurn() ? "Black" : "White") 
			<< endl << moves.size() << " Moves:\n";

		Tile currentOriginTile = Tile();
		for (auto s : moves)
		{
			if (s.isShortRook())
			{
				wcout << "\n0-0";
			}
			else if (s.isLongRook())
			{
				wcout << "\n0-0-0";
			}
			else
			{
				Tile newOriginTile = s.getOrigin();
				if (currentOriginTile != newOriginTile)
				{
					currentOriginTile = newOriginTile;
					wcout << endl << (char)(currentOriginTile.getColumn() + 'a')
						<< (char)(currentOriginTile.getRow() + '1')
						<< " -> ";
				}
				else
				{
					wcout << ", ";
				}

				Tile destinationTile = s.getDestination();
				wcout << (char)(destinationTile.getColumn() + 'a') 
					<< (char)(destinationTile.getRow() + '1');
			}			
		}

		wcout << endl;

		while (1) 
		{
			wcout << "\nMove: ";
			string command;
			cin >> command;

			transform(command.begin(), command.end(), command.begin(), ::tolower);

			if (command == "undo")
			{
				position->undoMove();
				break;
			}
			else
			{
				Move * input = &ui->getOpponentMove(command);

				auto iterator = find(moves.begin(), moves.end(), *input);
				if (iterator == moves.end())
					continue;

				Move* move = &*iterator;

				if (*input == *move)
				{
					position->updatePosition(move);
					break;
				}
			}
		}		
	}
}
