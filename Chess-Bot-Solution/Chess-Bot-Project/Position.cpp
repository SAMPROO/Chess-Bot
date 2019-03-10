#include "Position.h"
#include "Rook.h"
#include "Horse.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"

const double 	kingValue	=	100, 
				queenValue	=	9, 
				rookValue	=	5, 
				bishopValue =	3.25, 
				horseValue	=	3, 
				pawnValue	=	1;

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

Position::Position(MoveStack * moveStack) {

	_moveStack = moveStack;

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

void Position::updatePosition(Move* move, bool realMove)
{
	if (realMove)
		_moveStack->push(*move);

	int row = getTurn() ? 7 : 0;

	// Short Rook
	if (move->isShortRook()) {
		board[6][row] = board[4][row]; // King to new position
		board[4][row] = NULL; // Clear old position
		board[5][row] = board[7][row]; // Rook to new position
		board[7][row] = NULL; // Clear old position

		if (realMove)
		{
			setShortRookMoved();
			setKingMoved();
		}
	}
	// Long Rook
	else if (move->isLongRook()) {
		board[2][row] = board[4][row]; // King to new position
		board[4][row] = NULL; // Clear old position
		board[3][row] = board[0][row]; // Rook to new position
		board[0][row] = NULL; // Clear old position

		if (realMove) 
		{
			setLongRookMoved();
			setKingMoved();
		}
		
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

		// removed if (chessPiece != NULL)

		if (realMove)
		{
			switch (chessPiece->getCode())
			{
			case BR:
			case WR:
				if (originColumn)
					setLongRookMoved();
				else
					setShortRookMoved();
				break;

			case BK:
			case WK:
				setKingMoved();
				break;
			}

			_moveStack->setCapturedPiece(board[destinationColumn][destinationRow]);
			
			if (move->isEnPassant())
				_moveStack->setEnPassant(board[destinationColumn][destinationRow + (getTurn() ? 1 : -1)]);

			if (move->isPromoted())
			{
				wstring Q = getTurn() ? bQueen->getUnicode() : wQueen->getUnicode();
				wstring H = getTurn() ? bHorse->getUnicode() : wHorse->getUnicode();
				wstring R = getTurn() ? bRook->getUnicode() : wRook->getUnicode();
				wstring B = getTurn() ? bBishop->getUnicode() : wBishop->getUnicode();

				wcout << "\n" << Q << " " << H << " " << R << " " << B
					<< "\nQ H R B" 
					<< "\n\nPromote to: " ;

				char selection;
				do{
					cin >> selection;
					selection = tolower(selection);
				} while (selection != 'q' && selection != 'h' && selection != 'r' && selection != 'b');

				switch (selection)
				{
				case 'q':
					chessPiece = getTurn() ? bQueen : wQueen;
					break;
				case 'h':
					chessPiece = getTurn() ? bHorse : wHorse;
					break;
				case 'r':
					chessPiece = getTurn() ? bRook : wRook;
					break;
				case 'b':
					chessPiece = getTurn() ? bBishop : wBishop;
					break;
				}
			}
		}

		if (move->isEnPassant())
			board[destinationColumn][destinationRow + (getTurn() ? 1 : -1)] = NULL;

		board[destinationColumn][destinationRow] = chessPiece;
		board[originColumn][originRow] = NULL;
	}

	if (realMove)
		changeTurn();
}

void Position::undoMove()
{
	if (_moveStack->isEmpty())
		return;

	Move move = _moveStack->getMove();

	int row = getTurn() ? 7 : 0;

	// Undo short Rook
	if (move.isShortRook()) {
		board[4][row] = board[6][row]; // King to new position
		board[6][row] = NULL; // Clear old position
		board[7][row] = board[5][row]; // Rook to new position
		board[5][row] = NULL; // Clear old position
	}
	// Undo long Rook
	else if (move.isLongRook()) {
		board[4][row] = board[2][row]; // King to new position
		board[2][row] = NULL; // Clear old position
		board[0][row] = board[3][row]; // Rook to new position
		board[3][row] = NULL; // Clear old position
	}
	// Undo normal move
	else
	{
		Tile tileOrigin = move.getOrigin();
		Tile tileDestination = move.getDestination();

		int destinationRow = tileDestination.getRow();
		int destinationColumn = tileDestination.getColumn();

		int originRow = tileOrigin.getRow();
		int originColumn = tileOrigin.getColumn();

		if (move.isPromoted() == false)
			board[originColumn][originRow] = board[destinationColumn][destinationRow];
		else
			board[originColumn][originRow] = !getTurn() ? bPawn : wPawn;


		board[destinationColumn][destinationRow] = _moveStack->getCapturedPiece();
		
		if (move.isEnPassant())
			board[destinationColumn][destinationRow + (getTurn() ? 1 : -1)] = _moveStack->getEnPassant();
	}

	_moveStack->pop();
}

int Position::getTurn()
{
	return _moveStack->getTurn();
}

void Position::changeTurn()
{
	_moveStack->changeTurn();
}

bool Position::getKingMoved(int color)
{
	return _moveStack->getCastlingBools(color);
}

bool Position::getShortRookMoved(int color)
{
	return _moveStack->getCastlingBools(2 + color);
}

bool Position::getLongRookMoved(int color)
{
	return _moveStack->getCastlingBools(4 + color);
}

void Position::setKingMoved()
{
	_moveStack->setCastlingBools(getTurn(), true);
}

void Position::setShortRookMoved()
{
	_moveStack->setCastlingBools(2 + getTurn(), true);
}

void Position::setLongRookMoved()
{
	_moveStack->setCastlingBools(4 + getTurn(), true);
}

void Position::getLegalMoves(std::list<Move>& moves, int turn)
{
	getRawMoves(moves, turn);
	addEnPassant(moves, turn);
	addCastling(moves, turn);
	isCheck(moves, turn);
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

void Position::isCheck(std::list<Move>& moves, int turn)
{
	Tile king;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			ChessPiece * chessPiece = board[i][j];

			if (chessPiece != NULL && (chessPiece->getCode() == WK || chessPiece->getCode() == BK) && chessPiece->getColor() == getTurn())
			{
				king = Tile(j, i);
			}
		}
	}	

	std::list<Move> safeMoves;

	for (Move move : moves)
	{
		Position newPosition = *this;

		newPosition.updatePosition(&move, false);

		Tile kingTile = move.getOrigin() == king ? move.getDestination() : king;

		if (newPosition.isTileThreatened(kingTile, !turn) == false)
		{
			safeMoves.push_back(move);
		}
	}

	moves = safeMoves;
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

			moves.push_back(Move(true, false));		

		// long rook
		if (getLongRookMoved(turn) == false
			&& board[3][row] == NULL 
			&& board[2][row] == NULL
			&& board[1][row] == NULL
			&& isTileThreatened(Tile(row, 3), !turn) == false
			&& isTileThreatened(Tile(row, 2), !turn) == false)
			
			moves.push_back(Move(false, true));
	}
	
}

void Position::addEnPassant(std::list<Move>& moves, int turn)
{
	if (_moveStack->isEmpty())
		return;

	Move lastMove = _moveStack->getMove();
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

			moves.push_back(Move(origin, destination, true));
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

MinMaxReturn Position::minimax(int depth, double alpha, double beta, int turn)
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
		returnValue._evaluationValue = evaluate();
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
		MinMaxReturn value = newPosition.minimax(depth - 1, alpha, beta, !turn);

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

	if (isTileThreatened(Tile(kx, ky), !turn))
		return 0; // tasapeli (patti)
	else
		return turn ? 1000000 : -1000000;	// matti
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
double Position::evaluate()
{
	// Vakiokertoimet kuvaavat eri tekijöiden tärkeyttä suhteessa toisiinsa.
	// Kertoimien asettaminen edellyttää testaamista ja sovellusalueen (shakki)
	// osaamista. Tässä materiaalin tärkeydeksi on asetettu 1. Muiden tekijöiden
	// kertoimet ovat yleensä tätä pienempiä, koska materiaali on kaikkein
	// tärkein yksittäinen tekijä.
	const double materialMultiplier = 1.0;

	// Materiaali
	double material = calculateMaterialValue();

	// Palautetaan eri tekijöiden painotettu summa.
	return materialMultiplier * material; // + linjaKerroin * linjat + ... jne
}


double Position::calculateMaterialValue()
{
	double whiteValue = 0;
	double blackValue = 0;

	for (int x = 0; x < 8; x++) 
	{
		for (int y = 0; y < 8; y++) 
		{
			if (board[x][y] != NULL)
			{
				if (board[x][y]->getColor())
					blackValue += board[x][y]->getValue();
				else
					whiteValue += board[x][y]->getValue();
			}
		}
	}

	return whiteValue - blackValue;
}
