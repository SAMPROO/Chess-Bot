#include "Position.h"

Position::Position() {

	// Initialization of white pieces 
	board[0][0] = new ChessPiece(L"\u2656", 0, WR);
	board[1][0] = new ChessPiece(L"\u2658", 0, WH);
	board[2][0] = new ChessPiece(L"\u2657", 0, WB);
	board[3][0] = new ChessPiece(L"\u2654", 0, WK);
	board[4][0] = new ChessPiece(L"\u2655", 0, WQ);
	board[5][0] = new ChessPiece(L"\u2657", 0, WB);
	board[6][0] = new ChessPiece(L"\u2658", 0, WH);
	board[7][0] = new ChessPiece(L"\u2656", 0, WR);

	for (int i = 0; i < 8; i++)
	{
		board[i][1] = new ChessPiece(L"\u2659", 0, WP);
	}

	// Initialization of empty positions 
	for (int i = 0; i < 8; i++)
	{
		for (int j = 2; j < 6; j++)
		{
			board[i][j] = 0;
		}
	}

	// Initialization of black pieces 
	for (int i = 0; i < 8; i++)
	{
		board[i][6] = new ChessPiece(L"\u265F", 1, BP);
	}

	board[0][7] = new ChessPiece(L"\u265C", 1, BR);
	board[1][7] = new ChessPiece(L"\u265E", 1, BH);
	board[2][7] = new ChessPiece(L"\u265D", 1, BB);
	board[3][7] = new ChessPiece(L"\u265A", 1, BK);
	board[4][7] = new ChessPiece(L"\u265B", 1, BQ);
	board[5][7] = new ChessPiece(L"\u265D", 1, BB);
	board[6][7] = new ChessPiece(L"\u265E", 1, BH);
	board[7][7] = new ChessPiece(L"\u265C", 1, BR);
}

void Position::updatePostion(Move* move)
{
	Tile tileOrigin = move->getOrigin();
	Tile tileDestination = move->getDestination();

	int destinationRow = tileDestination.getRow();
	int destinationColumn = tileDestination.getColumn();

	int originRow = tileOrigin.getRow();
	int originColumn = tileOrigin.getColumn();

	board[destinationColumn][destinationRow] = board[originColumn][originRow];
	board[originColumn][originRow] = 0;
}

//
//VK, L"\u2654	
//VD, L"\u2655	
//VT, L"\u2656	 
//VL, L"\u2657	
//VR, L"\u2658	
//VS, L"\u2659"

//MK, L"\u265A	
//MD, L"\u265B
//MT, L"\u265C�
//ML, L"\u265D"
//MR, L"\u265E"
//MS, L"\u265F"
