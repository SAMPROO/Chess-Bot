#include "UI.h"
#include <windows.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

UI::UI(Position* position)
{
	_position = position;
}

void UI::drawBoard()
{
	// Enables wcout to print unicode
	_setmode(_fileno(stdout), _O_U16TEXT);

	// For switching background color on/off
	bool color = false;

	// Printing the board and the pieces
	for (int i = 7; i >= 0; i--)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		std::wcout << i + 1;

		for (int j = 0; j < 8; j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color ? 96 : 240);

			ChessPiece* temp = _position->board[j][i];

			if (temp)
			{
				std::wcout << " " << temp->getUnicode() << " ";
			}
			else
			{
				std::wcout << "   ";
			}			

			if(j < 7)
				color = !color;
		}

		std::wcout << "\n";
	}

	std::wcout << "  a  b  c  d  e  f  g  h";
}