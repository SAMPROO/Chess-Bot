#include "Position.h"
#include "Rook.h"
#include "Horse.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"

#include <chrono>

const double 	kingValue = 200,
		queenValue	=	9,
		rookValue	=	5,
		bishopValue	=	3.25,
		horseValue	=	3,
		pawnValue	=	1,
		pieceCombinedValue	=	/*kingValue + */queenValue + (rookValue + bishopValue + horseValue) * 2 + pawnValue * 8;

ChessPiece* Position::wRook = new Rook(L"\u2656", 0, WR, rookValue);
ChessPiece* Position::wHorse = new Horse(L"\u2658", 0, WH, horseValue);
ChessPiece* Position::wBishop = new Bishop(L"\u2657", 0, WB, bishopValue);
ChessPiece* Position::wKing = new King(L"\u2654", 0, WK, kingValue);
ChessPiece* Position::wQueen = new Queen(L"\u2655", 0, WQ, queenValue);
ChessPiece* Position::wPawn = new Pawn(L"\u2659", 0, WP, pawnValue);
			
ChessPiece* Position::bRook = new Rook(L"\u265C", 1, BR, rookValue);
ChessPiece* Position::bHorse = new Horse(L"\u265E", 1, BH, horseValue);
ChessPiece* Position::bBishop = new Bishop(L"\u265D", 1, BB, bishopValue);
ChessPiece* Position::bKing = new King(L"\u265A", 1, BK, kingValue);
ChessPiece* Position::bQueen = new Queen(L"\u265B", 1, BQ, queenValue);
ChessPiece* Position::bPawn = new Pawn(L"\u265F", 1, BP, pawnValue);

Position::Position() {

	_positionStack = new PositionStack();

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			board[i][j] = NULL;

	// Initialization of white pieces 
	board[0][0] = wRook;
	board[1][0] = wHorse;
	board[2][0] = wBishop;
	board[3][0] = wQueen;
	board[4][0] = wKing;
	board[5][0] = wBishop;
	board[6][0] = wHorse;
	board[7][0] = wRook;

	//Initialize pawns
	for (int i = 0; i < 8; i++)
	{
		board[i][1] = wPawn;
		board[i][6] = bPawn;
	}

	board[0][7] = bRook;
	board[1][7] = bHorse;
	board[2][7] = bBishop;
	board[3][7] = bQueen;
	board[4][7] = bKing;
	board[5][7] = bBishop;
	board[6][7] = bHorse;
	board[7][7] = bRook;
}

void Position::updatePosition(Move* move, bool realMove, bool aiMove)
{
	/*if (realMove)
		_moveStack->push(*move);*/

	_previousMove = *move;

	if (realMove)
		_positionStack->push(new Position(*this));

	//int turn = getTurn();
	int row = _turn ? 7 : 0;

	// Short Rook
	if (move->isShortRook()) {
		board[6][row] = board[4][row]; // King to new position
		board[4][row] = NULL; // Clear old position
		board[5][row] = board[7][row]; // Rook to new position
		board[7][row] = NULL; // Clear old position

		/*if (realMove)
		{*/
		setShortRookMoved();
		setKingMoved();
		//}

		/*if (turn)
			_blackKing = &Tile(row, 6);
		else
			_whiteKing = &Tile(row, 6);*/
		
	}
	// Long Rook
	else if (move->isLongRook()) {
		board[2][row] = board[4][row]; // King to new position
		board[4][row] = NULL; // Clear old position
		board[3][row] = board[0][row]; // Rook to new position
		board[0][row] = NULL; // Clear old position

		/*if (realMove) 
		{*/
		setLongRookMoved();
		setKingMoved();
		//}
		
		/*if (turn)
			_blackKing = &Tile(row, 2);
		else
			_whiteKing = &Tile(row, 2);*/
	}
	// Normal move
	else 
	{
		Tile tileOrigin = move->getOrigin();
		Tile tileDestination = move->getDestination();

		int destinationRow = tileDestination.getRow();
		int destinationColumn = tileDestination.getColumn();

		int originRow = tileOrigin.getRow();
		int originColumn = tileOrigin.getColumn();

		ChessPiece * chessPiece = board[originColumn][originRow];
		auto pieceCode = chessPiece->getCode();

		/*if (pieceCode == BK)
			_blackKing = &tileDestination;
		else if (pieceCode == WK)
			_whiteKing = &tileDestination;*/

		/*if (realMove)
		{*/
			switch (pieceCode)
			{
			case BR:
			case WR:
				if (originColumn)
					setShortRookMoved();
				else
					setLongRookMoved();
				break;

			case BK:
			case WK:
				setKingMoved();
				break;
			}

			/*_moveStack->setCapturedPiece(board[destinationColumn][destinationRow]);
			
			if (move->isEnPassant())
				_moveStack->setEnPassant(board[destinationColumn][destinationRow + (turn ? 1 : -1)]);*/
		//}
		if (move->isPromoted() > -1)
		{
			switch (move->isPromoted())
			{
			case 0:
				chessPiece = _turn ? bRook : wRook;
				break;
			case 1: 
				chessPiece = _turn ? bHorse : wHorse;
				break;
			case 2:
				chessPiece = _turn ? bBishop : wBishop;
				break;
			case 3:
				chessPiece = _turn ? bQueen : wQueen;
				break;
			}

			//if (aiMove == false)
			//{
			//	wstring Q = turn ? bQueen->getUnicode() : wQueen->getUnicode();
			//	wstring H = turn ? bHorse->getUnicode() : wHorse->getUnicode();
			//	wstring R = turn ? bRook->getUnicode() : wRook->getUnicode();
			//	wstring B = turn ? bBishop->getUnicode() : wBishop->getUnicode();

			//	wcout << "\n" << Q << " " << H << " " << R << " " << B
			//		<< "\nQ H R B"
			//		<< "\n\nPromote to: ";

			//	char selection;
			//	do {
			//		cin >> selection;
			//		selection = tolower(selection);
			//	} while (selection != 'q' && selection != 'h' && selection != 'r' && selection != 'b');

			//	switch (selection)
			//	{
			//	case 'q':
			//		chessPiece = turn ? bQueen : wQueen;
			//		break;
			//	case 'h':
			//		chessPiece = turn ? bHorse : wHorse;
			//		break;
			//	case 'r':
			//		chessPiece = turn ? bRook : wRook;
			//		break;
			//	case 'b':
			//		chessPiece = turn ? bBishop : wBishop;
			//		break;
			//	}
			//}
			//else
			//{
			//	//AI CHOOSES WHICH TO PROMOTE TO
			//	chessPiece = turn ? bQueen : wQueen;
			//	chessPiece = turn ? bHorse : wHorse;

			//	Position newPosition = *this;
			//	newPosition.updatePosition(move, false);
			//}

		}

		if (move->isEnPassant())
			board[destinationColumn][destinationRow + (_turn ? 1 : -1)] = NULL;

		board[destinationColumn][destinationRow] = chessPiece;
		board[originColumn][originRow] = NULL;
	}

	/*if (realMove)
		*/
	changeTurn();
}

void Position::undoMove()
{
	if (_positionStack->isEmpty())
		return;

	_positionStack->pop();

	Position * previousPosition = _positionStack->getPosition();
	if (previousPosition == NULL)
		return;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			board[i][j] = previousPosition->board[i][j];
			

	for (int i = 0; i < 6; i++)
		_castlingBools[i] = previousPosition->_castlingBools[i];
		
	_turn = previousPosition->_turn;

	_previousMove = previousPosition->_previousMove;

	_positionStack->pop();

	//delete previousPosition;

	//Move move = _positionStack->getMove();

	//int row = getTurn() ? 7 : 0;
	//int turn = getTurn();

	//// Undo short Rook
	//if (move.isShortRook()) {
	//	board[4][row] = board[6][row]; // King to new position
	//	board[6][row] = NULL; // Clear old position
	//	board[7][row] = board[5][row]; // Rook to new position
	//	board[5][row] = NULL; // Clear old position

	//	/*if (turn)
	//		_blackKing = &Tile(row, 4);
	//	else
	//		_whiteKing = &Tile(row, 4);*/
	//}
	//// Undo long Rook
	//else if (move.isLongRook()) {
	//	board[4][row] = board[2][row]; // King to new position
	//	board[2][row] = NULL; // Clear old position
	//	board[0][row] = board[3][row]; // Rook to new position
	//	board[3][row] = NULL; // Clear old position

	//	/*if (turn)
	//		_blackKing = &Tile(row, 4);
	//	else
	//		_whiteKing = &Tile(row, 4);*/
	//}
	//// Undo normal move
	//else
	//{
	//	Tile tileOrigin = move.getOrigin();
	//	Tile tileDestination = move.getDestination();

	//	int destinationRow = tileDestination.getRow();
	//	int destinationColumn = tileDestination.getColumn();

	//	int originRow = tileOrigin.getRow();
	//	int originColumn = tileOrigin.getColumn();

	//	if (move.isPromoted() == false)
	//		board[originColumn][originRow] = board[destinationColumn][destinationRow];
	//	else
	//		board[originColumn][originRow] = !turn ? bPawn : wPawn;


	//	board[destinationColumn][destinationRow] = _positionStack->getCapturedPiece();
	//	
	//	if (move.isEnPassant())
	//		board[destinationColumn][destinationRow + (turn ? 1 : -1)] = _positionStack->getEnPassant();

	//	/*auto pieceCode = board[originColumn][originRow]->getCode();

	//	if (pieceCode == BK)
	//		_blackKing = &tileOrigin;
	//	else if (pieceCode == WK)
	//		_whiteKing = &tileOrigin;*/
	//}

	//_positionStack->pop();
}

int Position::getTurn()
{
	//return _moveStack->getTurn();
	return _turn;
}

void Position::changeTurn()
{
	//_moveStack->changeTurn();
	_turn = !_turn;
}

bool Position::getKingMoved(int color)
{
	//return _moveStack->getCastlingBools(color);
	return _castlingBools[color];
}

bool Position::getShortRookMoved(int color)
{
	//return _moveStack->getCastlingBools(2 + color);
	return _castlingBools[2 + color];
}

bool Position::getLongRookMoved(int color)
{
	//return _moveStack->getCastlingBools(4 + color);
	return _castlingBools[4 + color];

}

void Position::setKingMoved()
{
	//_moveStack->setCastlingBools(getTurn(), true);
	_castlingBools[_turn] = true;
}

void Position::setShortRookMoved()
{
	//_moveStack->setCastlingBools(2 + getTurn(), true);
	_castlingBools[2 + _turn] = true;

}

void Position::setLongRookMoved()
{
	//_moveStack->setCastlingBools(4 + getTurn(), true);
	_castlingBools[4 + _turn] = true;

}

//enum startOrder { R, H, B, Q, K, P, Sr, Lr };

									   // R, H, B, Q, K, P, 0-0, 0-0-0
int middleGamePieceOrder[8]	=			{ 7, 1, 2, 3, 6, 0, 5, 4 };
int endGamePieceOrder[8]	=			{ 1, 2, 4, 0, 7, 3, 6, 5 };

int queenThreatenedMiddleGame[8]	=	{ 3, 2, 4, 0, 7, 1, 6, 5 };
int queenThreatenedEndGame[8]		=	{ 1, 2, 4, 0, 7, 3, 6, 5 };


bool inEndGamePhase;
bool queenThreatened;

bool my_compare(Move &a, Move &b)
{
	if (queenThreatened)
	{
		switch (inEndGamePhase)
		{
		case 0:
			return queenThreatenedMiddleGame[a._piece] < queenThreatenedMiddleGame[b._piece];
		case 1:
			return queenThreatenedEndGame[a._piece] < queenThreatenedEndGame[b._piece];
		}
		return 0;
	}
	else
	{
		switch (inEndGamePhase)
		{
		case 0:
			return middleGamePieceOrder[a._piece] < middleGamePieceOrder[b._piece];
		case 1:
			return endGamePieceOrder[a._piece] < endGamePieceOrder[b._piece];
		}
		return 0;
	}
	
}

void Position::getLegalMoves(list<Move>& moves, int turn)
{
	queenThreatened = getRawMoveAndIsCheck(moves, turn);
	//getRawMoves(moves, turn);
	addEnPassant(moves, turn);
	addCastling(moves, turn);

	//queenThreatened = isCheck(moves, turn);

	auto temp = calculateMaterialValue();
	double whiteMaterial = temp.first;
	double blackMaterial = temp.second;

	inEndGamePhase = (turn ? blackMaterial : whiteMaterial) <= (pieceCombinedValue / 2);

	moves.sort(my_compare);
}

void Position::getRawMoves(std::list<Move>& moves, int turn)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			ChessPiece * chessPiece = board[j][i];

			if (chessPiece != NULL && chessPiece->getColor() == turn)
			{
				chessPiece->getMoves(moves, &Tile(i, j), this, turn);
			}
		}
	}
}

bool Position::isCheck(std::list<Move>& moves, int turn)
{
	//Tile king = turn ? *_blackKing : *_whiteKing;
	Tile king;
	Tile queen;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			ChessPiece * chessPiece = board[i][j];

			if (chessPiece != NULL && (chessPiece->getCode() == WK || chessPiece->getCode() == BK) && chessPiece->getColor() == getTurn())
			{
				king = Tile(j, i);
			}
			else if (chessPiece != NULL && (chessPiece->getCode() == WQ || chessPiece->getCode() == BQ) && chessPiece->getColor() == getTurn())
			{
				queen = Tile(j, i);
			}
		}
	}	

	std::list<Move> safeMoves;
	bool queenThreatened = false;

	for (Move move : moves)
	{
		Position newPosition = *this;

		newPosition.updatePosition(&move, false);

		Tile kingTile = move.getOrigin() == king ? move.getDestination() : king;
		Tile queenTile = move.getOrigin() == queen ? move.getDestination() : queen;


		if (newPosition.isTileThreatened(kingTile, !turn) == false)
			safeMoves.push_back(move);

		//Check if queen is threatened for pieceMoveOrder
		if (newPosition.isTileThreatened(queenTile, !turn) == true && queenThreatened == false)
			queenThreatened = true;
		else if (newPosition.isTileThreatened(queenTile, !turn) == false && queenThreatened == false)
			queenThreatened =  false;
		
	}

	moves = safeMoves;
	return queenThreatened;

}

bool Position::getRawMoveAndIsCheck(std::list<Move>& moves, int turn)
{
	//Tile king = turn ? *_blackKing : *_whiteKing;
	Tile king;
	Tile queen;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			ChessPiece * chessPiece = board[i][j];

			if (chessPiece != NULL && chessPiece->getColor() == turn)
			{
				chessPiece->getMoves(moves, &Tile(j, i), this, turn);
			}

			if (chessPiece != NULL && (chessPiece->getCode() == WK || chessPiece->getCode() == BK) && chessPiece->getColor() == getTurn())
			{
				king = Tile(j, i);
			}
			else if (chessPiece != NULL && (chessPiece->getCode() == WQ || chessPiece->getCode() == BQ) && chessPiece->getColor() == getTurn())
			{
				queen = Tile(j, i);
			}
		}
	}

	std::list<Move> safeMoves;
	bool queenThreatened = false;

	for (Move move : moves)
	{
		Position newPosition = *this;

		newPosition.updatePosition(&move, false);

		Tile kingTile = move.getOrigin() == king ? move.getDestination() : king;
		Tile queenTile = move.getOrigin() == queen ? move.getDestination() : queen;


		if (newPosition.isTileThreatened(kingTile, !turn) == false)
			safeMoves.push_back(move);

		//Check if queen is threatened for pieceMoveOrder
		if (newPosition.isTileThreatened(queenTile, !turn) == true && queenThreatened == false)
			queenThreatened = true;
		else if (newPosition.isTileThreatened(queenTile, !turn) == false && queenThreatened == false)
			queenThreatened = false;

	}

	moves = safeMoves;
	return queenThreatened;

}

void Position::addCastling(std::list<Move>& moves, int turn)
{
	//// Linnoituksien huomioiminen
	//// 1. Kuningas ei saa olla liikkunut
	//// 2. Torni ei saa olla liikkunut
	//// 3. Kuningas ei saa olla shakattuna
	//// 4. Ruutujen pitää olla tyhjät
	//// 5. Ruudut eivät saa olla uhattuja

	int row = turn ? 7 : 0;

	if (getKingMoved(turn) == false && isTileThreatened(Tile(row, 4), !turn) == false)
	{
		// short rook
		if (getShortRookMoved(turn) == false
			&& board[5][row] == NULL 
			&& board[6][row] == NULL
			&& isTileThreatened(Tile(row, 5), !turn) == false
			&& isTileThreatened(Tile(row, 6), !turn) == false)

			moves.push_back(Move(true, false, 6));		

		// long rook
		if (getLongRookMoved(turn) == false
			&& board[3][row] == NULL 
			&& board[2][row] == NULL
			&& board[1][row] == NULL
			&& isTileThreatened(Tile(row, 3), !turn) == false
			&& isTileThreatened(Tile(row, 2), !turn) == false)
			
			moves.push_back(Move(false, true, 7));
	}
	
}

void Position::addEnPassant(std::list<Move>& moves, int turn)
{
	if (_positionStack->isEmpty())
		return;

	Move lastMove = _positionStack->getPosition()->_previousMove;
	if (lastMove.getOrigin().getRow() != (!turn ? 6 : 1))
		return;

	Tile lastDestination = lastMove.getDestination();
	if (lastDestination.getRow() != (!turn ? 4 : 3))
		return;

	ChessPiece * lastPiece = board[lastDestination.getColumn()][lastDestination.getRow()];
	if (lastPiece != NULL && lastPiece->getCode() != (!turn ? BP : WP))
		return;

	for (int i = 0; i < 2; i++)
	{
		int column = lastDestination.getColumn() + (i ? -1 : 1);

		if (column < 0 || column > 7)
			continue;

		ChessPiece * chessPiece = board[column][!turn ? 4 : 3];
		if (chessPiece != NULL && chessPiece->getCode() == (turn ? BP : WP))
		{
			Tile origin = Tile(!turn ? 4 : 3, column);
			Tile destination = Tile(lastDestination.getRow() + (turn ? -1 : 1), lastDestination.getColumn());

			moves.push_back(Move(origin, destination, 0, true));
		}
	}	
}

bool Position::isTileThreatened(Tile tile, int enemyColor)
{
	std::list<Move> enemyMoves;
	getRawMoves(enemyMoves, enemyColor);

	for (Move move : enemyMoves)
	{
		Tile origin = move.getOrigin();
		ChessPiece * chessPiece = board[origin.getColumn()][origin.getRow()];

		if (chessPiece != NULL && move.getDestination() == tile)
		{
			if (chessPiece->getCode() == WP || chessPiece->getCode() == BP)
			{
				return origin.getColumn() != tile.getColumn();
			}

			return true;
		}
	}

	return false;
}

MinMaxReturn Position::minimax(int depth, double alpha, double beta, int turn, Move currentMove, long startTime)
{
	MinMaxReturn returnValue;

	std::list<Move> moves;
	
	getLegalMoves(moves, turn);

	// Rekursion kantatapaus 1: peli on loppu koska laillisia siirtoja ei ole.
	if (moves.size() == 0)
	{
		returnValue._evaluationValue = endResult(turn);
		return returnValue;
	}

	// Rekursion kantatapaus 2: katkaisusyvyydessä
	if (depth == 0)
	{
		returnValue._evaluationValue = evaluate(turn, currentMove);
		return returnValue;
	}

	if (&returnValue != NULL) {

		long time = clock();
		long timeGone = time - startTime;

		if (_maxTime - (timeGone * 0.001f) <= 0)
			return returnValue;

	}
	// alustetaan paluuarvo huonoimmaksi mahdolliseksi.
	returnValue._evaluationValue = (turn ? inf : -inf);

	// Rekursioaskel: kokeillaan jokaista laillista siirtoa
	for (auto move : moves)
	{
		// Seuraaja-asema (tehdään nykyisessä asemassa siirto s).
		Position newPosition = *this;
		newPosition.updatePosition(&move, false);

		// Rekursiivinen kutsu.
		MinMaxReturn value = newPosition.minimax(depth - 1, alpha, beta, !turn, move, startTime);		

		// Tutkitaan ollaan löydetty uusi paras siirto.
		if ((turn && value._evaluationValue < returnValue._evaluationValue) || 
			!turn && value._evaluationValue > returnValue._evaluationValue)
		{
			// Löydettiin uusi paras siirto.
			returnValue._evaluationValue = value._evaluationValue;
			returnValue._bestMove = move;

			// Alpha-Beta:
			if (turn)
				beta = fmin(beta, value._evaluationValue);
			else
				alpha = fmax(alpha, value._evaluationValue);

			if (beta <= alpha)
				break;
		}		
	}
	return returnValue;
}


double Position::endResult(int turn)
{
	// Asemassa ei ole enää laillisia siirtoja. Etsitään siirtovuoroisen pelaajan
	// kuningas; jos kuningas on uhattu, on pelaaja hävinnyt (muuten tasapeli, "patti").

	// Kuninkaan sijainti (x,y).
	//Tile king = turn ? *_blackKing : *_whiteKing;
	ChessPiece * king = turn ? bKing : wKing;
	int kx, ky;
	for (int x = 0; x < 8; ++x)
	{
		for (int y = 0; y < 8; ++y)
		{
			if (board[x][y] == king)
			{
				kx = x;
				ky = y;
			}
		}
	}

	if (isTileThreatened(Tile(kx, ky)/*king*/, !turn)) {

		return 0; // tasapeli (patti)
	}
	else
	{
		return turn ? 1000000 : -1000000;	// matti
	}
}

/*
	Aseman numeerinen arviointi eri tekijöiden perusteella, esim.

	1. Nappuloiden arvo ("materiaali")
		Daami = 9
		Torni = 5
		Lähetti = 3,25
		Ratsu = 3
		Sotilas = 1

	2. Kuninkaan turvallisuus/hyvyys
		Jos avaus tai keskipeli, niin hyvä että kunigas g1 tai b1/c1
		Loppupelissä vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
		vai olla estämässä vastustajan korotusta siksi ei oteta kantaa.

	3. Sentralisaatio (keskustan hallinta)
		Nappulat ovat yleensä paremmin laudan keskellä kuin laidoilla.

	4. Linjojen hallinta
		Tornit sijaitsevat hyvin avoimilla linjoilla (= linja jolla ei ole yhtään omaa sotilasta).

	jne. jne.
*/
double Position::evaluate(int turn, Move move)
{
	// Vakiokertoimet kuvaavat eri tekijöiden tärkeyttä suhteessa toisiinsa.
	// Kertoimien asettaminen edellyttää testaamista ja sovellusalueen (shakki)
	// osaamista. Tässä materiaalin tärkeydeksi on asetettu 1. Muiden tekijöiden
	// kertoimet ovat yleensä tätä pienempiä, koska materiaali on kaikkein
	// tärkein yksittäinen tekijä.
	const double materialMultiplier = 1.0;
	const double pieceTileMultiplier = 0.1;

	// Materiaali
	auto temp = calculateMaterialValue();
	double whiteMaterial = temp.first;
	double blackMaterial = temp.second;

	bool inEndGamePhase = (turn ? blackMaterial : whiteMaterial) <= (pieceCombinedValue / 2);

	double material = whiteMaterial - blackMaterial;
	double pieceTileValue = calculatePieceTileValueAndCenterControl(inEndGamePhase);
	double castlingValue = calculateCastlingValue(move);
	double kingProtectionValue = calculateKingSafetyValue(inEndGamePhase);

	Position newPos;

	

	//bool queenThreatened = ((move._piece == 3) && (isTileThreatened(move.getOrigin(), turn)));

	//if (queenThreatened)
	//double middleControlValue = calculateMiddleControlValue();

	// Palautetaan eri tekijöiden painotettu summa.
	return materialMultiplier * material + pieceTileMultiplier * pieceTileValue + castlingValue * pieceTileMultiplier + kingProtectionValue * pieceTileMultiplier; // + linjaKerroin * linjat + ... jne
}


pair<double, double> Position::calculateMaterialValue()
{
	double whiteValue = 0;
	double blackValue = 0;

	for (int x = 0; x < 8; x++) 
	{
		for (int y = 0; y < 8; y++) 
		{
			if (board[x][y] != NULL)
			{
				//board[x][y]->getColor() ? (blackValue += board[x][y]->getValue()) : (whiteValue += board[x][y]->getValue());

				if (board[x][y]->getColor() )
					blackValue += board[x][y]->getValue();
				else
					whiteValue += board[x][y]->getValue();
			}
		}
	}

	return make_pair(whiteValue, blackValue);
}



const int pawnMiddleGameTable[/*64*/] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		-21, -16, -6, -1, -1, -6, -16, -21,
		-21, -16, -6, 4, 4, -6, -16, -21,
		-21, -16, -1, 9, 9, -1, -16, -21,
		-14, -8, 6, 17, 17, 6, -8, -14,
		-5, 1, 14, 29, 29, 14, 1, -5,
		7, 11, 23, 39, 39, 23, 11, 7,
		0, 0, 0, 0, 0, 0, 0, 0 };

const int pawnEndGameTable[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	5, -10, -20, -25, -25, -20, -10, 5,
	5, -10, -20, -25, -25, -20, -10, 5,
	10, -5, -15, -20, -20, -15, -5, 10,
	18, 2, -8, -15, -15, -8, 2, 18,
	30, 14, 1, -10, -10, 1, 14, 30,
	45, 30, 16, 5, 5, 16, 30, 45,
	0, 0, 0, 0, 0, 0, 0, 0 };

const int horseMiddleGameTable[] = {
	-69, -19, -24, -14, -14, -24, -19, -69,
	-54, -39, -9, 11, 11, -9, -39, -54,
	-39, 1, 31, 21, 21, 31, 1, -39,
	-39, 11, 41, 36, 36, 41, 11, -39,
	-39, 41, 51, 51, 51, 51, 41, -39,
	-39, 46, 61, 71, 71, 61, 46, -39,
	-39, 21, 41, 41, 41, 41, 21, -39,
	-59, -39, -29, -29, -29, -29, -39, -59 };


const int horseEndGameTable[] = {
	-63, -53, -43, -43, -43, -43, -53, -63,
	-53, -43, 18, 28, 28, 18, -43, -53,
	-43, 18, 48, 38, 38, 48, 18, -43,
	-43, 38, 58, 68, 68, 58, 38, -43,
	-43, 38, 73, 78, 78, 73, 38, -43,
	-43, 28, 78, 73, 73, 78, 28, -43,
	-53, -43, 38, 48, 48, 38, -43, -53,
	-63, -53, -43, -43, -43, -43, -53, -63 };


const int bishopMiddleGameTable[] = {
	-30, -25, -20, -20, -20, -20, -25, -30,
	-28, 11, 6, 1, 1, 6, 11, -28,
	-25, 6, 16, 11, 11, 16, 6, -25,
	1, 1, 16, 21, 21, 16, 1, 1,
	1, 21, 21, 26, 26, 21, 21, 1,
	1, 11, 21, 26, 26, 21, 11, 1,
	-10, 11, 1, 1, 1, 1, 11, -10,
	-20, -18, -16, -14, -14, -16, -18, -20 };


const int bishopEndGameTable[] = {
	-38, -18, -8, 2, 2, -8, -18, -38,
	-18, -8, 2, 7, 7, 2, -8, -18,
	-8, 2, 10, 12, 12, 10, 2, -8,
	2, 12, 16, 20, 20, 16, 12, 2,
	2, 12, 17, 22, 22, 17, 12, 2,
	-8, 2, 20, 22, 22, 20, 2, -8,
	-18, -8, 0, 12, 12, 0, -8, -18,
	-38, -18, -8, 2, 2, -8, -18, -38 };


const int rookMiddleGameTable[] = {
	-8, -6, 2, 7, 7, 2, -6, -8,
	-8, -6, 2, 7, 7, 2, -6, -8,
	-8, -6, 6, 7, 7, 6, -6, -8,
	-8, -6, 6, 7, 7, 6, -6, -8,
	-8, -6, 6, 8, 8, 6, -6, -8,
	-8, -6, 6, 10, 10, 6, -6, -8,
	2, 2, 7, 12, 12, 7, 2, 2,
	-8, -6, 2, 7, 7, 2, -6, -8 };


const int rookEndGameTable[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0 };


const int queenMiddleGameTable[] = {
	-26, -16, -6, 4, 4, -6, -16, -26,
	-16, -11, -1, 4, 4, -1, -11, -16,
	-6, -6, -1, 4, 4, -1, -6, -6,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4 };


const int queenEndGameTable[] = {
	-46, -41, -31, -26, -26, -31, -41, -46,
	-31, -26, -16, -6, -6, -16, -26, -31,
	-16, -1, 14, 24, 24, 14, -1, -16,
	-6, 9, 24, 34, 34, 24, 9, -6,
	-6, 9, 24, 34, 34, 24, 9, -6,
	-6, 9, 24, 34, 34, 24, 9, -6,
	-16, 4, 19, 29, 29, 19, 4, -16,
	-26, -6, -1, 4, 4, -1, -6, -26 };


const int kingMiddleGameTable[] = {
	-20, 10, 10, -10, -10, 10, 10, -20,
	-30, -30, -30, -35, -35, -30, -30, -30,
	-40, -40, -45, -50, -50, -45, -40, -40,
	-50, -50, -55, -60, -60, -55, -50, -50,
	-55, -55, -60, -70, -70, -60, -55, -55,
	-55, -55, -60, -70, -70, -60, -55, -55,
	-55, -55, -60, -70, -70, -60, -55, -55,
	-55, -55, -60, -70, -70, -60, -55, -55 };

const int kingEndGameTable[] = {
	-30, -25, -15, -10, -10, -15, -25, -30,
	-15, -10, 0, 10, 10, 0, -10, -15,
	0, 15, 30, 40, 40, 30, 15, 0,
	10, 25, 40, 50, 50, 40, 25, 10,
	10, 25, 40, 50, 50, 40, 25, 10,
	10, 25, 40, 50, 50, 40, 25, 10,
	0, 20, 35, 45, 45, 35, 20, 0,
	-10, 10, 15, 20, 20, 15, 10, -10 };

double getGameTableValue(int index, int code, bool inEndGamePhase)
{

	switch (code)
	{
	case BR:
	case WR:
		return inEndGamePhase ? rookEndGameTable[index] : rookMiddleGameTable[index];

	case BH:
	case WH:
		return inEndGamePhase ? horseEndGameTable[index] : horseMiddleGameTable[index];

	case BB:
	case WB:
		return inEndGamePhase ? bishopEndGameTable[index] : bishopMiddleGameTable[index];

	case BQ:
	case WQ:
		return inEndGamePhase ? queenEndGameTable[index] : queenMiddleGameTable[index];

	case BK:
	case WK:
		return inEndGamePhase ? kingEndGameTable[index] : kingMiddleGameTable[index];

	case BP:
	case WP:
		return inEndGamePhase ? pawnEndGameTable[index] : pawnMiddleGameTable[index];
	default:
		return 0;
	}

}

const int middleControlTable[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 10, 10, 10, 10, 0, 0,
	0, 0, 10, 20, 20, 10, 0, 0,
	0, 0, 10, 25, 25, 10, 0, 0,
	0, 0, 20, 25, 25, 20, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0 };

double Position::calculatePieceTileValueAndCenterControl(bool inEndGamePhase)
{
	double whiteValue = 0;
	double blackValue = 0;

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (board[x][y] != NULL)
			{
				int index = y * 8 + x + 1;

				if (board[x][y]->getColor())					
					blackValue += getGameTableValue(index, board[x][y]->getCode(), inEndGamePhase) + middleControlTable[index];
				else
					whiteValue += getGameTableValue(index, board[x][y]->getCode(), inEndGamePhase) + middleControlTable[index];
			}
		}
	}

	return whiteValue - blackValue;
}

double Position::calculateCastlingValue(Move currentMove)
{
	// Short Rook
	if (currentMove.isShortRook())
		return 130;
	// Long Rook
	else if (currentMove.isLongRook())
		return 150;
	else
		return 0;
}

double Position::calculateKingSafetyValue(bool inEndGamePhase)
{
	double value = 0;

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (board[x][y] != NULL && (board[x][y]->getCode() == WK || board[x][y]->getCode() == BK) && board[x][y]->getColor() == getTurn())
			{
				
				//Liian väsyny korjaa sä.. ota kommentit pois ja kato mitä sanoo

				/*if (y < 7)
					if (board[x][y + 1] != NULL && board[x][y + 1]->getColor == _turn)
						value += 20.0;
				if (y > 0)
					if(board[x][y - 1] != NULL && board[x][y - 1]->getColor == _turn)
					value += 20.0;


				if (x < 7)
					if (board[x + 1][y] != NULL && board[x + 1][y]->getColor == _turn)
					value += 20.0;
				if (x > 0)
					if (board[x - 1][y] != NULL && board[x - 1][y]->getColor == _turn)
					value += 20.0;


				if (x < 7)
					if (board[x + 1][y + 1] != NULL && board[x + 1][y + 1]->getColor == _turn)
					value += 20.0;
				if (x < 7 && y > 0)
					if (board[x + 1][y - 1] != NULL && board[x + 1][y - 1]->getColor == _turn)
					value += 20.0;


				if (y < 7 && x > 0)
					if (board[x - 1][y + 1] != NULL && board[x - 1][y + 1]->getColor == _turn)
					value += 20.0;
				if (y > 0 && x > 0)
					if (board[x - 1][y - 1] != NULL && board[x - 1][y - 1]->getColor == _turn)
					value += 20.0;*/

				return value;
			}
		}
	}
	return value;
}

//double Position::calculatePieceTileValue(Move currentMove, int turn)
//{
//	int row = getTurn() ? 7 : 0;
//
//	// Short Rook
//	if (currentMove.isShortRook())
//		return 50;
//	// Long Rook
//	else if (currentMove.isLongRook())
//		return 60;
//
//	int originColumn = currentMove.getOrigin().getColumn();
//	int originRow = currentMove.getOrigin().getRow();
//
//	int destinationColumn = currentMove.getDestination().getColumn();
//	int destinationRow = currentMove.getDestination().getRow();
//
//	ChessPiece *chessPiece = board[destinationColumn][destinationRow];
//
//	int color = chessPiece->getColor();
//
//	if (color)
//	{
//		/*destinationIndex = 63 - destinationIndex;
//		originIndex = 63 - originIndex;*/
//
//		originColumn = 7 - originColumn;
//		originRow = 7 - originRow;
//
//		destinationColumn = 7 - destinationColumn;
//		destinationRow = 7 - destinationRow;
//	}
//
//	int destinationIndex = destinationRow * 9 + destinationColumn;
//	int originIndex = originRow * 9 + originColumn;
//
//	int pieceTileValue = 0;
//
//	switch (chessPiece->getCode())
//	{
//	case BR:
//	case WR:
//		if (rookMiddleGameTable[originIndex] < rookMiddleGameTable[destinationIndex])
//			pieceTileValue = rookMiddleGameTable[destinationIndex];
//		break;
//
//	case BH:
//	case WH:
//		if (horseMiddleGameTable[originIndex] < horseMiddleGameTable[destinationIndex])
//			pieceTileValue = horseMiddleGameTable[destinationIndex];
//		break;
//
//	case BB:
//	case WB:
//		if (bishopMiddleGameTable[originIndex] < bishopMiddleGameTable[destinationIndex])
//			pieceTileValue = bishopMiddleGameTable[destinationIndex];
//		break;
//
//	case BQ:
//	case WQ:
//		if (queenMiddleGameTable[originIndex] < queenMiddleGameTable[destinationIndex])
//			pieceTileValue = queenMiddleGameTable[destinationIndex];
//		break;
//
//	case BK:
//	case WK:
//		if (kingMiddleGameTable[originIndex] < kingMiddleGameTable[destinationIndex])
//			pieceTileValue = kingMiddleGameTable[destinationIndex];
//		break;
//
//	case BP:
//	case WP:
//		if (pawnMiddleGameTable[originIndex] < pawnMiddleGameTable[destinationIndex])
//			pieceTileValue = pawnMiddleGameTable[destinationIndex];
//		break;
//	}
//
//	return (color ? -1 : 1) * pieceTileValue;
//}



