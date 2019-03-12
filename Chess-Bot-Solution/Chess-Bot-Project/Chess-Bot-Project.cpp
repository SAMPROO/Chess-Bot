#include <iostream>
#include <algorithm>
#include <limits>
#include <chrono>
#include "UI.h"
#include "Position.h"

int main()
{
	Position* position = new Position(new MoveStack());
	UI* ui = new UI(position);

	char colorChar;
	do
	{
		wcout << "\nSelect color (B, W): ";
		cin >> colorChar;
		colorChar = tolower(colorChar);
	} while (colorChar != 'b' && colorChar != 'w');
	

	int color = colorChar == 'w';

	while (1)
	{
		ui->drawBoard();

		int turn = position->getTurn();

		list<Move> moves;

		position->getLegalMoves(moves, turn);

		wcout << "\nColor: " << (position->getTurn() ? "Black" : "White") 
			<< endl << moves.size() << " Moves:\n";

		Tile currentOriginTile = Tile();
		for (auto s : moves)
		{
			if (s.isShortRook())
				wcout << "\n0-0";
			else if (s.isLongRook())
				wcout << "\n0-0-0";
			else
			{
				Tile newOriginTile = s.getOrigin();
				if (currentOriginTile != newOriginTile)
				{
					wcout << endl;

					currentOriginTile = newOriginTile;
					wcout << (char)(currentOriginTile.getColumn() + 'a')
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

				if (s.isPromoted() > -1)
				{
					char promotedChar;
					switch (s.isPromoted())
					{
					case 0:
						promotedChar = 'T';
						break;
					case 1:
						promotedChar = 'H';
						break;
					case 2:
						promotedChar = 'L';
						break;
					case 3:
						promotedChar = 'D';
						break;
					}
					wcout << promotedChar;
				}
			}			
		}

		wcout << endl;

		// AI
		if (color == turn)
		{
			//position->timer = 2.0;
			auto begin = chrono::high_resolution_clock::now();

			MinMaxReturn aiChoice = position->minimax(4, -position->inf, position->inf, turn, Move());

			auto end = chrono::high_resolution_clock::now();
			auto dur = end - begin;
			auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
			wcout << "Duration: " << ms << endl;

			double evaluationValue = aiChoice._evaluationValue;

			wcout << "MinMax value: " << evaluationValue << "\n";
			Move aiMove = aiChoice._bestMove;

			if (&aiMove == NULL)
			{
				if (evaluationValue == 0)
				{
					wcout << "!!!DRAW!!!" << endl;
				}
				else if (evaluationValue > 0)
				{
					wcout << "!!!WHITE WON!!!" << endl;
				}
				else
				{
					wcout << "!!!BLACK WON!!!" << endl;
				}
			}

			if (aiMove.isShortRook())
				wcout << "0-0";
			else if (aiMove.isLongRook())
				wcout << "0-0-0";
			else
			{
				Tile origin = aiMove.getOrigin();
				Tile destination = aiMove.getDestination();
				wcout << (char)(origin.getColumn() + 'a') << (char)(origin.getRow() + '1') << "-"
					<< (char)(destination.getColumn() + 'a') << (char)(destination.getRow() + '1');
			}

			wcout << endl;

			position->updatePosition(&aiMove, true, true);

			/*wcout << "Press Enter to Continue";
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');*/
		}
		else
		{
			// player
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
}
