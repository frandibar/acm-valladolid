
/* @JUDGE_ID:  40922FK  10024  C++  */
    
/**************************************************************************
 Solution to Problem 10024 - Curling up the cube
 by: Francisco Dibar
 date: Dec-28-2004
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <cmath>		// pow

#define COLS	6
#define ROWS	6
#define DIM		36		// ROWS*COLS

#define DIMMAPS	56

using namespace std;

// vec_maps guarda los mapas validos 
// (representacion binaria) son 60 (56 id distintos)
int vec_maps[] = {	380,
							497,
							498,
							500,
							636,
							726,
							739,
							753,
							754,
							756,
							760,
							876,
							978,
							994,
							996,
							1000,
							1008,
							1148,
							1175,
							1182,
							1203,
							1209,
							1210,
							1212,
							1238,
							1251,
							1265,
							1266,
							1268,
							1272,
							1427,
							1433,
							1434,
							1490,
							1512,
							1714,
							1716,
							1938,
							2275,
							2290,
							2292,
							2296,
							2451,
							2457,
							2458,
							2514,
							2772,
							3171,
							3185,
							3186,
							3188,
							3225,
							3226,
							3282,
							3612,
							3730 };

///////////////////////////////////////////////////////////////////////////
int binsearch(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else		// found match
			return mid;
	}
	return -1;	// no match
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

	int bloques;
	cin >> bloques;

	for (int k = 0; (k < bloques) && (!cin.eof()); k++) {
		int mat_mapa[ROWS][COLS];
		int suma = 0;
		int xmin = COLS, xmax = 0, ymin = ROWS, ymax = 0;
		bool ok = false;
		// cargar el mapa en mat_mapa
		// si no hay 6 unos, ok = falso
		// obtengo el x del uno mas arriba, del mas abajo,
		// y el y del mas a la izquierda y mas a la derecha
		// para luego formar el id del mapa
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				cin >> mat_mapa[i][j];
				if (mat_mapa[i][j] == 1) {
					suma++;
					if (i < ymin) ymin = i;
					if (i > ymax) ymax = i;
					if (j < xmin) xmin = j;
					if (j > xmax) xmax = j;
				}
			}
		}
		if (suma == 6) {
			long id_mapa = 0;
			double exp = 11;
			// obtener el id del mapa
			for (int i = ymin; i <= ymax; i++) {
				for (int j = xmin; j <= xmax; j++) {
					if (mat_mapa[i][j] == 1)
						id_mapa += (long)pow(2,exp);
					exp--;
				}
			}
			ok = (binsearch(id_mapa, vec_maps, DIMMAPS) != -1);
		}
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

