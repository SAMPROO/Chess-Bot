#include <iostream>
#include "UI.h"
#include "Position.h"

int main()
{
    std::cout << "Hello World!\n"; 
	Position* position = new Position();
	UI* ui = new UI(position);

	ui->drawBoard();
}