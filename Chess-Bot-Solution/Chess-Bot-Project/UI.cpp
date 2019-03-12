#include <windows.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <stdlib.h>
#include "UI.h"

UI::UI(Position* position)
{
	_position = position;
}

void UI::drawBoard(bool colorSelection)
{
	// Enables wcout to print unicode
	_setmode(_fileno(stdout), _O_U16TEXT);

	// For switching background color on/off
	bool color = false;

	// Printing the board and the pieces
	for (int i = 7; i >= 0; i--)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		wcout << i + 1;

		for (int j = 0; j < 8; j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color ? 96 : 240);

			ChessPiece* temp = _position->board[j][colorSelection ? i : (7 - i)];

			if (temp)
			{
				wcout << " " << temp->getUnicode() << " ";
			}
			else
			{
				wcout << "   ";
			}

			if (j < 7)
				color = !color;
		}

		wcout << "\n";
	}

	wcout << "  a  b  c  d  e  f  g  h";
}

Move UI::getOpponentMove(string inputOpponentMove, bool colorSelection)
{
	Move opponentMove;

	if (inputOpponentMove == "0-0")
	{
		opponentMove = Move(true, false, 6);
	}
	else if (inputOpponentMove == "0-0-0")
	{
		opponentMove = Move(false, true, 7);
	}
	else
	{
		int i = 0;

		Tile tiles[2];

		for (int j = 0; j < 2; i += 3, j++)
		{
			int columnInt = inputOpponentMove[i] - 'a';
			int rowInt = inputOpponentMove[i + 1] - '1';

			rowInt = colorSelection ? rowInt : 7 - rowInt;

			if (rowInt < 0 || rowInt > 7 || columnInt < 0 || columnInt > 7)
				return opponentMove;

			tiles[j] = Tile(rowInt, columnInt);
		}

		int promotedTo = -1;

		if (inputOpponentMove.length() == 6)
		{
			// T/R/L/D
			switch (inputOpponentMove[6])
			{
			case 'T':
				promotedTo = 0;
				break;
			case 'R':
				promotedTo = 1;
				break;
			case 'L':
				promotedTo = 2;
				break;
			case 'D':
				promotedTo = 3;
				break;
			}
		}

		opponentMove = Move(tiles[0], tiles[1], 0, 0, promotedTo);
	}

	return opponentMove;
}