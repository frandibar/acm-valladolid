/* @JUDGE_ID:  40922FK  10196  C++  */
    
/**************************************************************************
 Solution to Problem 10196 - Check the Check
 by: Francisco Dibar
 date: Jul-10-2005
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#include <fstream>
//#define ONLINE_JUDGE 

// blanco abajo, negro arriba
#define WP		'P'	// peon blanco
#define WR		'R'	// torre blanca
#define WB		'B'	// alfil blanco
#define WQ		'Q'	// reina blanca
#define WK		'K'	// rey blanco
#define WN		'N'	// caballo blanco
#define BP		'p'	// peon negro
#define BR		'r'	// torre negra
#define BB		'b'	// alfil negro
#define BQ		'q'	// reina negra
#define BK		'k'	// rey negro
#define BN		'n'	// caballo negro

#define NO_CHECK	0
#define WHITE		1
#define BLACK		2

#define VACIO		'.'

using namespace std;

///////////////////////////////////////////////////////////////////////////
inline bool rook(char mat_tablero[][8], int i, int j, int ki, int kj, 
				char king)
{
	// izquierda y derecha
	if (i == ki) {
		// estan en la misma fila
		if (j < kj) {
			// el rey esta a la derecha, 
			// fijarse si no hay fichas entre ambos
			for (int m = j+1; m < kj; m++)
				if (mat_tablero[ki][m] != VACIO) 
					return false;	// hay ficha entre ambos
			return true;
		} else {
			// el rey esta a la izquierda, 
			// fijarse si no hay fichas entre ambos
			for (int m = j-1; m > kj; m--)
				if (mat_tablero[ki][m] != VACIO) 
					return false;	// hay ficha entre ambos
			return true;
		}
	} else if (j == kj) {		// arriba y abajo
		// estan en la misma columna
		if (i < ki) {
			// el rey esta por debajo, 
			// fijarse si no hay fichas entre ambos
			for (int m = i+1; m < ki; m++)
				if (mat_tablero[m][kj] != VACIO) 
					return false;	// hay ficha entre ambos
			return true;
		} else {
			// el rey esta por encima, 
			// fijarse si no hay fichas entre ambos
			for (int m = i-1; m > ki; m--)
				if (mat_tablero[m][kj] != VACIO) 
					return false;	// hay ficha entre ambos
			return true;
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////
inline bool bishop(char mat_tablero[][8], int i, int j, int ki, int kj, 
					char king)
{
	// antidiagonal (\)
	if (ki - kj == i - j) {
		// estan en la misma diagonal
		if (i < ki) {
			// el rey esta por debajo y a la derecha, 
			// chequear que no hay fichas entre ambas
			for (int m = i+1, n = 1; m < ki; m++, n++)
				if (mat_tablero[m][j+n] != VACIO) 
					return false;	// hay ficha entre ambos
			return true;
		} else {
			// el rey esta por encima y a la izquierda, 
			// fijarse si no hay fichas entre ambos
			for (int m = i-1, n = 1; m > ki; m--, n++)
				if (mat_tablero[m][j-n] != VACIO) 
					return false;	// hay ficha entre ambos
			return true;
		}
	} else if (i + j == ki + kj) {		// diagonal (/)
		// estan en la misma diagonal
		if (i < ki) {
			// el rey esta por debajo y a la izquierda, 
			// chequear que no hay fichas entre ambas
			for (int m = i+1, n = 1; m < ki; m++, n++)
				if (mat_tablero[m][j-n] != VACIO) 
					return false;	// hay ficha entre ambos
			return true;
		} else {
			// el rey esta por encima y a la derecha, ç
			// fijarse si no hay fichas entre ambos
			for (int m = i-1, n = 1; m > ki; m--, n++)
				if (mat_tablero[m][j+n] != VACIO) 
					return false;	// hay ficha entre ambos
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
inline bool knight(char mat_tablero[][8], int i, int j, int ki, int kj, 
					char king)
{
	// chequear que la distancia no sea mayor a dos en altura y ancho
	if ((abs(i - ki) <= 2) && (abs(j - kj) <= 2)) {
		//  k.
		//	  .
		//   n
		if ((i-2 >= 0) && (j-1 >= 0))
			if (mat_tablero[i-2][j-1] == king) 
				return true;
		//	k..
		//   n
		if ((i-1 >= 0) && (j-2 >= 0))
			if (mat_tablero[i-1][j-2] == king) 
				return true;
		//   .k
		//	  .
		//   n
		if ((i-2 >= 0) && (j+1 < 8))
			if (mat_tablero[i-2][j+1] == king) 
				return true;
		//	  ..k
		//   n
		if ((i-1 >= 0) && (j+2 < 8))
			if (mat_tablero[i-1][j+2] == king) 
				return true;
		//   n
		//	k..
		if ((i+1 < 8) && (j-2 >= 0))
			if (mat_tablero[i+1][j-2] == king) 
				return true;
		//   n
		//	  .
		//  k.
		if ((i+2 < 8) && (j-1 >= 0))
			if (mat_tablero[i+2][j-1] == king) 
				return true;
		//   n
		//	  .
		//   .k
		if ((i+2 < 8) && (j+1 < 8))
			if (mat_tablero[i+2][j+1] == king) 
				return true;
		//   n
		//	  ..k
		if ((i+1 < 8) && (j+2 < 8))
			if (mat_tablero[i+1][j+2] == king) 
				return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////
bool under_check(char mat_tablero[][8], int i, int j, int ki, int kj, 
				char king)
// (i,j) son las posiciones de la ficha
// (ki,kj) las posiciones del rey atacado
{
	switch (mat_tablero[i][j]) {

		case WP:	case BP:		// peon
			if (king == BK) {
				// el peon debe estar una fila por debajo del rey
				if (((i-1 == ki) && (j-1 == kj)) || 
					((i-1 == ki) && (j+1 == kj)))
					return true;
			} else
				// el peon debe estar una fila por encima del rey
				if (((i+1 == ki) && (j-1 == kj)) || 
					((i+1 == ki) && (j+1 == kj)))
					return true;
			break;
		
		case WR:	case BR: 	// torre
			return rook(mat_tablero, i, j, ki, kj, king);
			break;

		case WB:	case BB:		// alfil
			return bishop(mat_tablero, i, j, ki, kj, king);
			break;

		case WN:	case BN:		// caballo
			return knight(mat_tablero, i, j, ki, kj, king);
			break;

		case WQ:	case BQ:		// reina
			int rook_check = 
				rook(mat_tablero, i, j, ki, kj, king);
			return (rook_check != NO_CHECK ? 
					rook_check : 
					bishop(mat_tablero, i, j, ki, kj, king));
			break;
	}
	return NO_CHECK;		// no llega nunca aca
}

///////////////////////////////////////////////////////////////////////////
int rey_en_jaque(char mat_tablero[][8], int wi, int wj, int bi, int bj)
// devuelve: 0 si no hay jaque, WHITE si el rey blanco esta en jaque, 
// o BLACK si es el negro
// no hay casos con ambos reyes en jaque
{
	// para cada ficha del tablero, verificar si pone en jaque al rey
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			char ficha = mat_tablero[i][j];
			if ((ficha == 'p') || (ficha == 'r') || (ficha == 'b') ||
				(ficha == 'q') || (ficha == 'n')) {
					// la ficha es negra, revisar jaque a rey blanco
					if (under_check(mat_tablero, i, j, wi, wj, WK))
						return WHITE;
			} else 
				if ((ficha == 'P') || (ficha == 'R') || (ficha == 'B') ||
					(ficha == 'Q') || (ficha == 'N')) {
					// la ficha es blanca, revisar jaque a rey negro
					if (under_check(mat_tablero, i, j, bi, bj, BK))
						return BLACK;
				}
		}
	}
	return NO_CHECK;
}

///////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	char mat_tablero[8][8];

	char pieza;
	cin >> pieza;
	int game = 0,	// cantidad de tableros
		 check;
	while (!cin.eof()) {
		bool empty = true;	// marca tablero vacio
		int wi = 0, // white_king(i,j)
			wj = 0, 
			bi = 0,	// black_king(i,j)
			bj = 0;	// guardan la posicion de los reyes
		game++;
		
		// cargar tablero
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				// determinar si es algun rey
				if (pieza == WK) {
					wi = i; wj = j;
					empty = false;
				} else if (pieza == BK) {
					bi = i; bj = j;
					empty = false;
				}
				// cargarlo en el tablero
				mat_tablero[i][j] = pieza;
				cin >> pieza;
			}
		}

		// resolver si el tablero no esta vacio
		if (!empty) {
			cout << "Game #" << game << ": ";
			check = rey_en_jaque(mat_tablero, wi, wj, bi, bj);
			switch (check) {
				case 0: 
					cout << "no ";
					break;
				case WHITE:
					cout << "white ";
					break;
				case BLACK:
					cout << "black ";
					break;
			}
			cout << "king is in check." << endl;
		}
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

