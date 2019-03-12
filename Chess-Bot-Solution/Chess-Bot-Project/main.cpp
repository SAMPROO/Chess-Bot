#include <iostream>
#include <algorithm>
#include <chrono>
#include "UI.h"
#include "Position.h"

int main()
{
	Position* position = new Position(new PositionStack(), 1000);
	UI* ui = new UI(position);

	char colorChar;
	do
	{
		wcout << "\nSelect color (B, W): ";
		cin >> colorChar;
		colorChar = tolower(colorChar);
	} while (colorChar != 'b' && colorChar != 'w');


	int colorSelection = colorChar == 'w';

	while (1)
	{
		ui->drawBoard(colorSelection);

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
					int y = currentOriginTile.getRow();
					wcout << (char)(currentOriginTile.getColumn() + 'a')
						<< (char)((colorSelection ? y : 7 - y) + '1')
						<< " -> ";
				}
				else
				{
					wcout << ", ";
				}

				Tile destinationTile = s.getDestination();
				int y = destinationTile.getRow();
				wcout << (char)(destinationTile.getColumn() + 'a')
					<< (char)((colorSelection ? y : 7 - y) + '1');

				if (s.isPromoted() > -1)
				{
					char promotedChar = 0;
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
		if (/*colorSelection == turn*/0)
		{
			//auto begin = chrono::high_resolution_clock::now();

			clock_t clockStart = clock();

			MinMaxReturn aiChoice = position->minimax(4, -position->inf, position->inf, turn, Move(), clockStart);

			auto duration = clock() - clockStart;

			/*auto end = chrono::high_resolution_clock::now();
			auto dur = end - begin;
			auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();*/
			wcout << "Duration: " << duration << endl;

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
				return 0;
			}

			if (aiMove.isShortRook())
				wcout << "0-0";
			else if (aiMove.isLongRook())
				wcout << "0-0-0";
			else
			{
				Tile origin = aiMove.getOrigin();
				Tile destination = aiMove.getDestination();
				wcout << (char)(origin.getColumn() + 'a') << (char)((colorSelection ? origin.getRow() : 7 - origin.getRow()) + '1') << "-"
					<< (char)(destination.getColumn() + 'a') << (char)((colorSelection ? destination.getRow() : 7 - destination.getRow()) + '1');
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
					Move * input = &ui->getOpponentMove(command, colorSelection);

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
