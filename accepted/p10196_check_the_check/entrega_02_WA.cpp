/* @JUDGE_ID:  40922FK  10196  C++  */
    
/******************************************************************************
 Solution to Problem 10196 - Check the Check
 by: Francisco Dibar
 date: Nov-29-2004
******************************************************************************/
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

////////////////////////////////////////////////////////////////////////////////
inline int rook(char mat_tablero[][8], int i, int j, int ki, int kj, int king, char rey_atacado)
{
	// izquierda y derecha
	if (i == ki) {
		// estan en la misma fila
		if (j < kj) {
			// el rey esta a la derecha, fijarse si no hay fichas entre ambos
			for (int m = j+1; m <= kj; m++)
				if (mat_tablero[ki][m] != VACIO) 
					if (mat_tablero[ki][m] == rey_atacado)
						return king;
					else return NO_CHECK;
		} else {
			// el rey esta a la izquierda, fijarse si no hay fichas entre ambos
			for (int m = j-1; m >= kj; m--)
				if (mat_tablero[ki][m] != VACIO) 
					if (mat_tablero[ki][m] == rey_atacado)
						return king;
					else return NO_CHECK;
		}
	} else if (j == kj) {		// arriba y abajo
		// estan en la misma columna
		if (i < ki) {
			// el rey esta por debajo, fijarse si no hay fichas entre ambos
			for (int m = i+1; m <= ki; m++)
				if (mat_tablero[m][kj] != VACIO) 
					if (mat_tablero[m][kj] == rey_atacado)
						return king;
					else return NO_CHECK;
		} else {
			// el rey esta por encima, fijarse si no hay fichas entre ambos
			for (int m = i-1; m >= ki; m--)
				if (mat_tablero[m][kj] != VACIO) 
					if (mat_tablero[m][kj] == rey_atacado)
						return king;
					else return NO_CHECK;
		}
	}
	return NO_CHECK;
}

////////////////////////////////////////////////////////////////////////////////
inline int bishop(char mat_tablero[][8], int i, int j, int ki, int kj, int king, char rey_atacado)
{
	// antidiagonal (\)
	if (ki - kj == i - j) {
		// estan en la misma diagonal
		if (i < ki) {
			// el rey esta por debajo y a la derecha, chequear que no hay fichas entre ambas
			for (int m = i+1, n = 1; m <= ki; m++, n++)
				if (mat_tablero[m][j+n] != VACIO) 
					if (mat_tablero[m][j+n] == rey_atacado)
						return king;
					else return NO_CHECK;
		} else {
			// el rey esta por encima y a la izquierda, fijarse si no hay fichas entre ambos
			for (int m = i-1, n = 1; m >= ki; m--, n++)
				if (mat_tablero[m][j-n] != VACIO) 
					if (mat_tablero[m][j-n] == rey_atacado)
						return king;
					else return NO_CHECK;
		}
	} else if (i + j == ki + kj) {		// diagonal (/)
		// estan en la misma diagonal
		if (i < ki) {
			// el rey esta por debajo y a la izquierda, chequear que no hay fichas entre ambas
			for (int m = i+1, n = 1; m <= ki; m++, n++)
				if (mat_tablero[m][j-n] != VACIO) 
					if (mat_tablero[m][j-n] == rey_atacado)
						return king;
					else return NO_CHECK;
		} else {
			// el rey esta por encima y a la derecha, fijarse si no hay fichas entre ambos
			for (int m = i-1, n = 1; m >= ki; m--, n++)
				if (mat_tablero[m][j+n] != VACIO) 
					if (mat_tablero[m][j+n] == rey_atacado)
						return king;
					else return NO_CHECK;
		}
	}
	return NO_CHECK;
}

////////////////////////////////////////////////////////////////////////////////
inline int knight(char mat_tablero[][8], int i, int j, int ki, int kj, int king, char rey_atacado)
{
	// chequear que la distancia no sea mayor a dos en altura y ancho
	if ((abs(i - ki) <= 2) && (abs(j - kj) <= 2)) {
		//  k.
		//	  .
		//   n
		if ((i-2 >= 0) && (j-1 >= 0))
			if (mat_tablero[i-2][j-1] == rey_atacado) 
				return king;
		//	k..
		//   n
		if ((i-1 >= 0) && (j-2 >= 0))
			if (mat_tablero[i-1][j-2] == rey_atacado) 
				return king;
		//   .k
		//	  .
		//   n
		if ((i-2 >= 0) && (j+1 < 8))
			if (mat_tablero[i-2][j+1] == rey_atacado) 
				return king;
		//	  ..k
		//   n
		if ((i-1 >= 0) && (j+2 < 8))
			if (mat_tablero[i-1][j+2] == rey_atacado) 
				return king;
		//   n
		//	k..
		if ((i+1 < 8) && (j-2 >= 0))
			if (mat_tablero[i+1][j-2] == rey_atacado) 
				return king;
		//   n
		//	  .
		//  k.
		if ((i+2 < 8) && (j-1 >= 0))
			if (mat_tablero[i+2][j-1] == rey_atacado) 
				return king;
		//   n
		//	  .
		//   .k
		if ((i+2 < 8) && (j+1 < 8))
			if (mat_tablero[i+2][j+1] == rey_atacado) 
				return king;
		//   n
		//	  ..k
		if ((i+1 < 8) && (j+2 < 8))
			if (mat_tablero[i+1][j+2] == rey_atacado) 
				return king;
	}
	return NO_CHECK;
}

////////////////////////////////////////////////////////////////////////////////
int under_check(char mat_tablero[][8], int i, int j, int ki, int kj, int king)
{
	char rey_atacado;
	// determinar el rey atacante
	(king == WHITE ? rey_atacado = WK : rey_atacado = BK);
	switch (mat_tablero[i][j]) {

		case WP:	case BP:		// peon
			if (king == BLACK) {
				// el peon debe estar una fila por debajo del rey
				if (((i-1 == ki) && (j-1 == kj)) || ((i-1 == ki) && (j+1 == kj)))
					return BLACK;
			} else
				// el peon debe estar una fila por encima del rey
				if (((i+1 == ki) && (j-1 == kj)) || ((i+1 == ki) && (j+1 == kj)))
					return WHITE;
			break;
		
		case WR:	case BR: 	// torre
			return rook(mat_tablero, i, j, ki, kj, king, rey_atacado);
			break;

		case WB:	case BB:		// alfil
			return bishop(mat_tablero, i, j, ki, kj, king, rey_atacado);
			break;

		case WN:	case BN:		// caballo
			return knight(mat_tablero, i, j, ki, kj, king, rey_atacado);
			break;

		case WQ:	case BQ:		// reina
			int rook_check = rook(mat_tablero, i, j, ki, kj, king, rey_atacado);
			return (rook_check != NO_CHECK ? rook_check : bishop(mat_tablero, i, j, ki, kj, king, rey_atacado));
			break;
	}
	return NO_CHECK;		// no llega nunca aca
}

////////////////////////////////////////////////////////////////////////////////
int hay_jaque(char mat_tablero[][8], int wi, int wj, int bi, int bj)
// devuelve: 0 si no hay jaque, WHITE si el rey blanco esta en jaque, o BLACK si es el negro
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			char ficha = mat_tablero[i][j];
			if ((ficha != VACIO) && (ficha != WK) && (ficha != BK)) {
				if (ficha > 'Z') {	// 'A' ...'a'
					// la ficha es negra, revisar jaque a rey blanco
					if (under_check(mat_tablero, i, j, wi, wj, WHITE))
						return WHITE;
				} else {
					// la ficha es blanca, revisar jaque a rey negro
					if (under_check(mat_tablero, i, j, bi, bj, BLACK))
						return BLACK;
				}
			}
		}
	}
	return NO_CHECK;
}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	char mat_tablero[8][8];

	char line[9];
	cin >> line;
	int game = 0,
		check;
	while (!cin.eof()) {
		int wi = 0, 
			wj = 0, 
			bi = 0, 
			bj = 0;	// guardan la posicion de los reyes
		game++;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				// determinar si el algun rey
				if (line[j] == WK) {
					wi = i; wj = j;
				} else if (line[j] == BK) {
					bi = i; bj = j;
				}
				// cargarlo en el tablero
				mat_tablero[i][j] = line[j];
			}
			cin >> line;
		}
		// resolver si el tablero no esta vacio
		if (wi || wj || bi || bj) {
			cout << "Game #" << game << ": ";
			check = hay_jaque(mat_tablero, wi, wj, bi, bj);
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
			cout << "king is in check" << endl;
		}
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

