#include <iostream>
#include "UI.h"
#include "Position.h"

int main()
{
	Position* position = new Position();
	UI* ui = new UI(position);

	while (true) 
	{
		ui->drawBoard();

		position->updatePostion(&ui->getOpponentMove());
	}	
}