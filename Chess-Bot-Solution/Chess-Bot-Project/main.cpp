#include <iostream>
#include <algorithm>
#include <chrono>
#include "UI.h"
#include "Position.h"

int main()
{
	Position* position = new Position();
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

		ui->printMoves(moves, colorSelection);

		// AI
		// Human against bot:	"colorSelection == turn"
		// Bot against bot:		"1"
		// Human agains human:	"0"
		if (/*colorSelection == turn*/1) 
		{
			clock_t clockStart = clock();

			MinMaxReturn aiChoice = position->minimax(4, -1000000, 1000000, turn, Move(), clockStart);

			auto duration = clock() - clockStart;

			wcout << "Duration: " << duration * 0.001f << endl;

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

			ui->printMove(aiMove, colorSelection);

			position->updatePosition(&aiMove, true, true);

			/*wcout << "Press Enter to Continue";
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');*/

			wcout << endl;
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
