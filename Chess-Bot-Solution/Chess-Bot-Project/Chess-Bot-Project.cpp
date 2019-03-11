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

		auto begin = chrono::high_resolution_clock::now();

		// AI
		MinMaxReturn aiChoice = position->minimax(3, -position->inf, position->inf, turn, Move());

		auto end = chrono::high_resolution_clock::now();
		auto dur = end - begin;
		auto ms = std::chrono::duration_cast<std::chrono::seconds>(dur).count();
		wcout << "Duration: " << ms << endl;

		wcout << "MinMax value: " << aiChoice._evaluationValue << "\n";
		Move aiMove = aiChoice._bestMove;
		
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

		position->updatePosition(&aiMove);

		/*wcout << "Press Enter to Continue";
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');*/

		//while (1) 
		//{
		//	wcout << "\nMove: ";
		//	string command;
		//	cin >> command;
		//
		//	transform(command.begin(), command.end(), command.begin(), ::tolower);
		//
		//	if (command == "undo")
		//	{
		//		position->undoMove();
		//		break;
		//	}
		//	else
		//	{
		//		Move * input = &ui->getOpponentMove(command);
		//
		//		auto iterator = find(moves.begin(), moves.end(), *input);
		//		if (iterator == moves.end())
		//			continue;
		//
		//		Move* move = &*iterator;
		//
		//		if (*input == *move)
		//		{
		//			position->updatePosition(move);
		//			break;
		//		}
		//	}
		//}		
	}
}
