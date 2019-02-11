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

		Move * input = &ui->getOpponentMove();

		std::list<Move> list;

		position->getLegalMovesFromOrigin(list, input->getOrigin());

		if (std::find(list.begin(), list.end(), *input) != list.end())
		{
			position->updatePostion(input);
		}	
	}	
}