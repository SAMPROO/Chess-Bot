#pragma once
#include "Move.h"


// luokka, jonka avulla saadaan palautettua minmax:ssa sek� siirto-olio ett� evaluointifunktion arvo
// Struct ajaisi saman asian. Kun ei rakenneta gettereit� ja settereit�, niin ei tarvita toteutus .cpp tiedostoa
class MinMaxReturn {
public:
	double _evaluationValue;
	Move _bestMove;
};