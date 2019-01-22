#include "UI.h"
#include <windows.h>
#include <iostream>

UI::UI(Position* position)
{
	_position = position;
}

void UI::drawBoard()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
		BACKGROUND_GREEN | BACKGROUND_BLUE);

	for (int i = 7; i >= 0; i--)
	{
		std::cout << i + 1;

		for (int j = 0; j < 8; j++)
		{
			std::wcout << " " << _position->board[i][j]->getUnicode();
		}

		std::cout << "\n";
	}

	std::cout << "  a b c d e f g h";
}