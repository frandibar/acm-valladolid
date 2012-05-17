
/* @JUDGE_ID:  40922FK  10024  C++  */
    
/**************************************************************************
 Solution to Problem 10024 - Curling up the cube
 by: Francisco Dibar
 date: Dec-22-2004
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 

#define COLS	6
#define ROWS	6
#define DIM		36		// ROWS*COLS

using namespace std;

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

	int bloques;
	cin >> bloques;

	for (int k = 0; (k < bloques) && (!cin.eof()); k++) {
		int mat_mapa[ROWS][COLS];
		int suma = 0;
		int fi = 0, fj = 0;
		bool first = true, ok = false;
		// cargar el mapa en mat_mapa
		// si no hay 6 unos, ok = falso
		// obtengo la posicion del primer 1 encontrado
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				cin >> mat_mapa[i][j];
				if (mat_mapa[i][j] == 1) {
					suma++;
					// guardar la posicion del 1er uno encontrado
					if (first) {
						fi = i;
						fj = j;
						first = false;
					}
				}
			}
		}
		if (suma == 6) 
			// el uno encontrado es alguno de los marcados con X
			// buscar en cada direccion
			/*
				X		X		X		X
			  111	  1111	1	 1111	
			   1		1	  111		1
				1				1		
			*/
			// condiciones de contorno
			if ((fi+3 < ROWS) && (fj-1 >= 0) && (fj+1 < COLS))
				if ((mat_mapa[fi+1][fj] == 1) && (mat_mapa[fi+2][fj] == 1) && (mat_mapa[fi+3][fj] == 1) && (mat_mapa[fi+1][fj-1] == 1) && (mat_mapa[fi+1][fj+1] == 1))
					ok = true;
				
			if ((fi+2 < ROWS) && (fj-1 >= 0) && (fj+2 < COLS))
				if ((mat_mapa[fi+1][fj] == 1) && (mat_mapa[fi+2][fj] == 1) && (mat_mapa[fi+1][fj-1] == 1) && (mat_mapa[fi+1][fj+1] == 1) && (mat_mapa[fi+1][fj+2] == 1))
					ok = true;

			if ((fi+3 < ROWS) && (fj-1 >= 0) && (fj+1 < COLS))
				if ((mat_mapa[fi+1][fj] == 1) && (mat_mapa[fi+2][fj] == 1) && (mat_mapa[fi+3][fj] == 1) && (mat_mapa[fi+2][fj-1] == 1) && (mat_mapa[fi+2][fj+1] == 1))
					ok = true;

			if ((fi+2 < ROWS) && (fj-2 >= 0) && (fj+1 < COLS))
				if ((mat_mapa[fi+1][fj] == 1) && (mat_mapa[fi+2][fj] == 1) && (mat_mapa[fi+1][fj-2] == 1) && (mat_mapa[fi+1][fj-1] == 1) && (mat_mapa[fi+1][fj+1] == 1))
					ok = true;

		// mostrar la salida
		if (ok)
			cout << "correct" << endl;
		else
			cout << "incorrect" << endl;
		
		// evitar ultima linea de mas
		if (k < bloques - 1) cout << endl;	
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

