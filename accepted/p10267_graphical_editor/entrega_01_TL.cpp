/* @JUDGE_ID:  40922FK  10267  C++  */
    
/******************************************************************************
 Solution to Problem 10267 - Graphical Editor
 by: Francisco Dibar
 date: Aug-05-2004
******************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
//#define ONLINE_JUDGE 

#define MAX		250

using namespace std;

////////////////////////////////////////////////////////////////////////////////
void pintar_region(vector< vector<char> >& mat_tablero, int x, int y, char c_new, char c_old) 
{
	mat_tablero[x][y] = c_new;
	// arriba
	if (x > 0) {
		if (mat_tablero[x-1][y] == c_old) 
			pintar_region(mat_tablero, x-1, y, c_new, c_old);
		// arriba izq
		if ((y > 0) && (mat_tablero[x-1][y-1] == c_old)) 
			pintar_region(mat_tablero, x-1, y-1, c_new, c_old);
		// arriba der
		if ((y < (int)mat_tablero.size()-1) && (mat_tablero[x-1][y+1] == c_old)) 
			pintar_region(mat_tablero, x-1, y+1, c_new, c_old);
	}
	// izquierda
	if ((y > 0) && (mat_tablero[x][y-1] == c_old)) 
		pintar_region(mat_tablero, x, y-1, c_new, c_old);
	// abajo
	if (x < (int)mat_tablero.size()-1) {
		if (mat_tablero[x+1][y] == c_old)  
			pintar_region(mat_tablero, x+1, y, c_new, c_old);
		// abajo izq
		if ((y > 0) && (mat_tablero[x+1][y-1] == c_old)) 
			pintar_region(mat_tablero, x+1, y-1, c_new, c_old);
		// abajo der
		if ((y < (int)mat_tablero.size()-1) && (mat_tablero[x+1][y+1] == c_old)) 
			pintar_region(mat_tablero, x+1, y+1, c_new, c_old);
	}
	// derecha
	if ((y < (int)mat_tablero.size()-1) && (mat_tablero[x][y+1] == c_old)) 
		pintar_region(mat_tablero, x, y+1, c_new, c_old);
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

	ostringstream os_output;
	char inst;
	vector< vector<char> > mat_tablero(MAX);

	cin >> inst;	// guarda la instruccion a leer
	// leer mientras la instruccion no sea X
	while (inst != 'X') {
		char c;
		int x1, x2, y1, y2, i, j, aux;
		switch (inst) {
			case 'I':	// crear una nueva imagen de N filas por M cols, color 0				
				// leer M y N
				int n, m;
				cin >> m >> n;
				mat_tablero.resize(n);
				for (i = 0; i < n; i++) {
					mat_tablero[i].resize(m);
					// colorear de blanco	
					for (j = 0; j < m; j++)
						mat_tablero[i][j] = 'O';
				}
				break;

			case 'C':	// borrar el tablero de blanco '0'
				for (i = 0; i < (int)mat_tablero.size(); i++) {
					for (j = 0; j < (int)mat_tablero[i].size(); j++)
						mat_tablero[i][j] = 'O';
				}
				break;
			
			case 'L':	// pinta el pixel x,y en color C
				cin >> x1 >> y1 >> c;
				mat_tablero[y1-1][x1-1] = c;
				break;

			case 'V':	// dibujar un segmento vertical de color c en la col x, entre filas y1 y y2 inclusive
				cin >> x1 >> y1 >> y2 >> c;				
				if (y1 > y2) {		// swap y1, y2
					aux = y2; y2 = y1; y1 = aux;
				}
				for (i = y1-1; i < y2; i++) 
					mat_tablero[i][x1-1] = c;
				break;

			case 'H':	// dibujar un segmento horizontal de color c en la col x, entre filas y1 y y2 inclusive
				cin >> x1 >> x2 >> y1 >> c;				
				if (x1 > x2) {		// swap
					aux = x2; x2 = x1; x1 = aux;
				}
				for (i = x1-1; i < x2; i++) 
					mat_tablero[y1-1][i] = c;
				break;

			case 'K':	// dibujar un rectangulo relleno de color c, (x1,y1) sup izq, (x2,y2) inf der
				cin >> x1 >> y1 >> x2 >> y2 >> c;				
				for (i = x1-1; i < x2; i++)
					for (j = y1-1; j < y2; j++)
						mat_tablero[i][j] = c;
				break;

			case 'F':	// pinta la region de color c
				cin >> x1 >> y1 >> c;				
				pintar_region(mat_tablero, x1-1, y1-1, c, mat_tablero[x1-1][y1-1]);
				break;
			
			case 'S':	// mostrar el nombre del archivo seguido del dibujo
				{
					string nombre;
					cin >> nombre;
					os_output << nombre << endl;
					// mostrar el tablero
					for (i = 0; i < (int)mat_tablero.size(); i++) {
						for (j = 0; j < (int)mat_tablero[i].size(); j++)
							os_output << mat_tablero[i][j];
						os_output << endl;
					}
				}
				break;

			default:						
				break;
		}
		cin >> inst;
	}

	cout << os_output.str();
	return 0;
}

/* @END_OF_SOURCE_CODE */

