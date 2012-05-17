/* @JUDGE_ID:  40922FK  10267  C++  */
    
/**************************************************************************
 Solution to Problem 10267 - Graphical Editor
 by: Francisco Dibar
 date: Feb-09-2004
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <string>
#include <queue>
//#define ONLINE_JUDGE 

#define MAX		260

using namespace std;

struct st_punto {
	int row, col;
};

///////////////////////////////////////////////////////////////////////////
void floodfill(vector<vector<char> >& mat_tablero, int row, int col,
				  char c_new, char c_old)
// row: fila inicial, col: col inicial
{
	if (mat_tablero[row][col] == c_new) return;

	queue<pair<int, int> > que_faltan;

	que_faltan.push(make_pair(row, col));
	while (!que_faltan.empty()) {
		pair<int, int> pos;
		pos = que_faltan.front();
		// puede ocurrir que apilo dos veces lo mismo
		que_faltan.pop();
		if (mat_tablero[pos.first][pos.second] == c_old) {
			mat_tablero[pos.first][pos.second] = c_new;
			if (pos.first-1 >= 0) {
				if (mat_tablero[pos.first-1][pos.second] == c_old)
					que_faltan.push(make_pair(pos.first-1, pos.second));
			}
			if (pos.first+1 < (int)mat_tablero.size()) {
				if (mat_tablero[pos.first+1][pos.second] == c_old)
					que_faltan.push(make_pair(pos.first+1, pos.second));
			}

			if (pos.second-1 >= 0) {
				if (mat_tablero[pos.first][pos.second-1] == c_old)
					que_faltan.push(make_pair(pos.first, pos.second-1));
			}

			if (pos.second+1 < (int)mat_tablero[0].size()) {
				if (mat_tablero[pos.first][pos.second+1] == c_old)
					que_faltan.push(make_pair(pos.first, pos.second+1));
			}
		}
	}
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

	char inst;
	vector< vector<char> > mat_tablero(MAX);

	cin >> inst;	// guarda la instruccion a leer
	// leer mientras la instruccion no sea X
	while (inst != 'X' && !cin.eof()) {
		char c;
		int x1, x2, y1, y2, i, j, aux;
		string nombre;
		switch (inst) {
			case 'I':	// crear imagen nueva de N filas x M cols, color O
				// leer M y N
				int n, m;
				cin >> m >> n;
				mat_tablero.resize(n);		
				for (i = 0; i < n; i++) {		
					mat_tablero[i].resize(m);	// mat_tablero[fila][col]
					// colorear de blanco	
					for (j = 0; j < m; j++)
						mat_tablero[i][j] = 'O';
				}
				break;

			case 'C':	// borrar el tablero de blanco 'O'
				for (i = 0; i < (int)mat_tablero.size(); i++) {
					for (j = 0; j < (int)mat_tablero[i].size(); j++)
						mat_tablero[i][j] = 'O';
				}
				break;
			
			case 'L':	// pinta el pixel (x,y) en color C			
							// (x,y) = (col,fila)
				cin >> x1 >> y1 >> c;
				mat_tablero[y1-1][x1-1] = c;
				break;

			case 'V':	// dibujar un segmento vertical de color c 
						// en la col x, entre filas y1 y y2 inclusive
				cin >> x1 >> y1 >> y2 >> c;				
				if (y1 > y2) {		// swap y1, y2
					aux = y2; y2 = y1; y1 = aux;
				}
				for (i = y1-1; i < y2; i++) 
					mat_tablero[i][x1-1] = c;
				break;

			case 'H':	// dibujar un segmento horizontal de color c 
						// en la col x, entre filas y1 y y2 inclusive
				cin >> x1 >> x2 >> y1 >> c;				
				if (x1 > x2) {		// swap
					aux = x2; x2 = x1; x1 = aux;
				}
				for (i = x1-1; i < x2; i++) 
					mat_tablero[y1-1][i] = c;
				break;

			case 'K':	// dibujar un rectangulo relleno de color c, 
						// supuestamente (x1,y1) sup izq, (x2,y2) inf der
						// pero por las dudas no lo supongo asi
				cin >> x1 >> y1 >> x2 >> y2 >> c;				
				if (x1 > x2) {		// swap
					aux = x2; x2 = x1; x1 = aux;
				}
				if (y1 > y2) {		// swap
					aux = y2; y2 = y1; y1 = aux;
				}
				for (i = x1-1; i < x2; i++)
					for (j = y1-1; j < y2; j++)
						mat_tablero[j][i] = c;
				break;

			case 'F':	// pinta la region de color c
				cin >> x1 >> y1 >> c;				
				// resto pues las coords empiezan en 0, y 1 para el user
				floodfill(mat_tablero, x1-1, y1-1, c, mat_tablero[y1-1][x1-1]);
				break;
			
			case 'S':	// mostrar nombre del archivo y dibujo
				cin >> nombre;
				cout << nombre << endl;
				// mostrar el tablero
				for (i = 0; i < (int)mat_tablero.size(); i++) {
					for (j = 0; j < (int)mat_tablero[i].size(); j++)
						cout << mat_tablero[i][j];
					cout << endl;
				}
				break;
				
			default:				
				// saltear linea		
				getline(cin, nombre);
		}
		cin >> inst;
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */


