/* @JUDGE_ID:  40922FK  10189  C++  */
    
/******************************************************************************
 Solution to Problem 10189 - Minesweeper
 by: Francisco Dibar
 date: Jul-17-2004
******************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
//#define ONLINE_JUDGE 

#define BOMBA_CHAR	'*'
#define BOMBA_INT		-1

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////
struct coord_bomba {
	int x, y;
};

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	ostringstream os_output;
	int n, m;	// dimensiones de la matriz
	cin >> n >> m;
	int caso = 1;
	while (!cin.eof() && m && n) {
		int bombas = 0;
		vector< vector<int> > mat_tablero(n);
		// cargo las bombas encontradas en coord_bomba;
		vector<coord_bomba> vec_coord_bombas;
		for (int i = 0; i < n; i++) {
			mat_tablero[i].resize(m);
			// leer la matriz y cargarla en mat_tablero
			for (int j = 0; j < m; j++) {
				char c;
				cin >> c;
				// si no se leyo una bomba, colocar 0, sino BOMBA_INT
//				mat_tablero[i][j] = 0;	// se inicializan automaticamente 0
				if (c == BOMBA_CHAR) {
					mat_tablero[i][j] = BOMBA_INT;
					bombas++;
					coord_bomba coord;
					coord.x = i;
					coord.y = j;
					vec_coord_bombas.push_back(coord);
				}
			}
		}
		// para cada bomba, modificar las celdas vecinas
		int dx[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
		int dy[] = { 1, -1, 0, 1, -1, 1, 0, -1 };
		for (int b = 0; b < bombas; b++) {					
			for (int i = 0; i < 8; i++) {
				int x = vec_coord_bombas[b].x + dx[i];
				int y = vec_coord_bombas[b].y + dy[i];
				// incrementar la celda si esta dentro de la grilla y no contiene bomba
				if ((x >= 0)&& (y >= 0) && (x < n) && (y < m) && (mat_tablero[x][y] != BOMBA_INT))
					mat_tablero[x][y]++;
			}
		}
		// mostrar la salida
		if (caso > 1)
			os_output << endl;
      
		os_output << "Field #" << caso++ << ":" << endl;
		for (int i = 0; (i < n); i++) {
			for (int j = 0; (j < m); j++) {
				if (mat_tablero[i][j] == BOMBA_INT) 
					os_output << BOMBA_CHAR;
				else
					os_output << mat_tablero[i][j];
			}
			os_output << endl;
		}
		cin >> n >> m;
	}
	cout << os_output.str();
	return 0;
}

/* @END_OF_SOURCE_CODE */

