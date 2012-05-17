
/* @JUDGE_ID:  40922FK  10024  C++  */
    
/**************************************************************************
 Solution to Problem 10024 - Curling up the cube
 by: Francisco Dibar
 date: Dec-19-2004
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>

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
		//int mat_mapa[ROWS][COLS];
		vector<vector<int> > mat_mapa(ROWS);
		int suma = 0;
		int fi = 0, fj = 0;
		bool first = true, ok = false;
		// cargar el mapa en mat_mapa
		// si no hay 6 unos, ok = falso
		// obtengo la posicion del primer 1 encontrado
		for (int i = 0; i < ROWS; i++) {
			mat_mapa[i].resize(COLS);
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
		if (suma == 6) {
			// el uno encontrado es alguno de los marcados con X
			// buscar en cada direccion
			/*
				X		X		X		X
			  111	  1111	1	 1111	
			   1		1	  111		1
				1				1		
			*/
			// uso vectores con "at" para evitar errores de contorno
			if (	(mat_mapa.at(fi+1).at(fj) == 1) && 
					(mat_mapa.at(fi+2).at(fj) == 1) && 
					(mat_mapa.at(fi+3).at(fj) == 1) && 
					(mat_mapa.at(fi+1).at(fj-1) == 1) && 
					(mat_mapa.at(fi+1).at(fj+1) == 1))
				ok = true;
			else if (	(mat_mapa.at(fi+1).at(fj) == 1) && 
							(mat_mapa.at(fi+2).at(fj) == 1) && 
							(mat_mapa.at(fi+1).at(fj-1) == 1) && 
							(mat_mapa.at(fi+1).at(fj+1) == 1) && 
							(mat_mapa.at(fi+1).at(fj+2) == 1))
				ok = true;
			else if (	(mat_mapa.at(fi+1).at(fj) == 1) && 
							(mat_mapa.at(fi+2).at(fj) == 1) && 
							(mat_mapa.at(fi+3).at(fj) == 1) && 
							(mat_mapa.at(fi+2).at(fj-1) == 1) && 
							(mat_mapa.at(fi+2).at(fj+1) == 1))
				ok = true;
			else if (	(mat_mapa.at(fi+1).at(fj) == 1) && 
							(mat_mapa.at(fi+2).at(fj) == 1) && 
							(mat_mapa.at(fi+1).at(fj-2) == 1) && 
							(mat_mapa.at(fi+1).at(fj-1) == 1) && 
							(mat_mapa.at(fi+1).at(fj+1) == 1))
				ok = true;
		} //else ok = false;
		
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
