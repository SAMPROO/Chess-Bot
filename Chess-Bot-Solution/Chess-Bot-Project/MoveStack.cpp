#include "MoveStack.h"

MoveStack::MoveStack() {
	_top = NULL;
}

MoveStack::~MoveStack() {
	while (!isEmpty())
		pop();
}

void MoveStack::push(Move move)
{
	MoveStack *temp = new MoveStack();
	temp->_move = move;

	for (int i = 0; i < 6; i++)
		temp->castlingBools[i] = castlingBools[i];

	temp->_next = _top;
	_top = temp;
}

void MoveStack::pop()
{
	if (!isEmpty())
	{
		MoveStack * oldtop = _top;
		_top = _top->_next;
		delete oldtop;
	}
}

bool MoveStack::isEmpty()
{
	return (_top == NULL);
}