/* @JUDGE_ID:  40922FK  10267  C++  */
    
/******************************************************************************
 Solution to Problem 10267 - Graphical Editor
 by: Francisco Dibar
 date: Aug-10-2004
******************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
//#define ONLINE_JUDGE 

#define MAX		250

using namespace std;

struct st_punto {
	int row, col;
};


////////////////////////////////////////////////////////////////////////////////
void pintar_region(vector< vector<char> >& mat_tablero, int row, int col, char c_new, char c_old) 
{
	st_punto punto, pnew;
	list<st_punto> lst_puntos_x_visitar;

	int cols = (int)mat_tablero[0].size();

	vector< vector<bool> > mat_tablero_visitados(MAX);
	// dimensionar e inicializar mat_tablero_visitados en false
	mat_tablero_visitados.resize(mat_tablero.size());		
	for (int i = 0; i < mat_tablero.size(); i++) 		
		mat_tablero_visitados[i].resize(mat_tablero[0].size());		// mat_tablero[fila][col]

	punto.row = row;
	punto.col = col;
	lst_puntos_x_visitar.push_back(punto);
	while (!lst_puntos_x_visitar.empty()) {
		punto = lst_puntos_x_visitar.front();
		lst_puntos_x_visitar.pop_front();
		// chequear para cada punto que rodea a punto, si tiene el color viejo, agregarlo a la lista.
		
		mat_tablero[punto.row][punto.col] = c_new;

		// arriba
		if (punto.row > 0) {
			if (mat_tablero[punto.row-1][punto.col] == c_old) {
				pnew.row = punto.row-1;
				pnew.col = punto.col;
				if (!mat_tablero_visitados[pnew.row][pnew.col]) {
					lst_puntos_x_visitar.push_back(pnew);
					mat_tablero_visitados[pnew.row][pnew.col] = true;
				}
			}
			// arriba izq
			if ((punto.col > 0) && (mat_tablero[punto.row-1][punto.col-1] == c_old)) {
				pnew.row = punto.row-1;
				pnew.col = punto.col-1;
				if (!mat_tablero_visitados[pnew.row][pnew.col]) {
					lst_puntos_x_visitar.push_back(pnew);
					mat_tablero_visitados[pnew.row][pnew.col] = true;
				}
			}
			// arriba der
			if ((punto.col < cols-1) && (mat_tablero[punto.row-1][punto.col+1] == c_old)) {
				pnew.row = punto.row-1;
				pnew.col = punto.col+1;
				if (!mat_tablero_visitados[pnew.row][pnew.col]) {
					lst_puntos_x_visitar.push_back(pnew);
					mat_tablero_visitados[pnew.row][pnew.col] = true;
				}
			}
		}
		// izquierda
		if ((punto.col > 0) && (mat_tablero[punto.row][punto.col-1] == c_old)) {
			pnew.row = punto.row;
			pnew.col = punto.col-1;
			if (!mat_tablero_visitados[pnew.row][pnew.col]) {
				lst_puntos_x_visitar.push_back(pnew);
				mat_tablero_visitados[pnew.row][pnew.col] = true;
			}
		}
		// abajo
		if (punto.row < (int)mat_tablero.size()-1) {
			if (mat_tablero[punto.row+1][punto.col] == c_old) {  
				pnew.row = punto.row+1;
				pnew.col = punto.col;
				if (!mat_tablero_visitados[pnew.row][pnew.col]) {
					lst_puntos_x_visitar.push_back(pnew);
					mat_tablero_visitados[pnew.row][pnew.col] = true;
				}
			}
			// abajo izq
			if ((punto.col > 0) && (mat_tablero[punto.row+1][punto.col-1] == c_old)) {
				pnew.row = punto.row+1;
				pnew.col = punto.col-1;
				if (!mat_tablero_visitados[pnew.row][pnew.col]) {
					lst_puntos_x_visitar.push_back(pnew);
					mat_tablero_visitados[pnew.row][pnew.col] = true;
				}
			}
			// abajo der
			if ((punto.col < cols-1) && (mat_tablero[punto.row+1][punto.col+1] == c_old)) {
				pnew.row = punto.row+1;
				pnew.col = punto.col+1;
				if (!mat_tablero_visitados[pnew.row][pnew.col]) {
					lst_puntos_x_visitar.push_back(pnew);
					mat_tablero_visitados[pnew.row][pnew.col] = true;
				}
			}
		}
		// derecha
		if ((punto.col < cols-1) && (mat_tablero[punto.row][punto.col+1] == c_old)) {
			pnew.row = punto.row;
			pnew.col = punto.col+1;
			if (!mat_tablero_visitados[pnew.row][pnew.col]) {
				lst_puntos_x_visitar.push_back(pnew);
				mat_tablero_visitados[pnew.row][pnew.col] = true;
			}
		}
	}
	
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
			case 'I':	// crear una nueva imagen de N filas por M cols, color O				
				// leer M y N
				int n, m;
				cin >> m >> n;
				mat_tablero.resize(n);		
				for (i = 0; i < n; i++) {		
					mat_tablero[i].resize(m);		// mat_tablero[fila][col]
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
			
			case 'L':	// pinta el pixel (x,y) en color C			(x,y) = (col,fila)
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
						mat_tablero[j][i] = c;
				break;

			case 'F':	// pinta la region de color c
				cin >> x1 >> y1 >> c;				
				pintar_region(mat_tablero, x1-1, y1-1, c, mat_tablero[y1-1][x1-1]);	// resto porque las coords empiezan en 0, y 1 para el user
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
				cin.ignore(255, '\n');		// saltear linea		
				break;
		}
		cin >> inst;
	}

	cout << os_output.str();
	return 0;
}

/* @END_OF_SOURCE_CODE */

