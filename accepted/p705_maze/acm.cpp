/* @JUDGE_ID:  40922FK  705  C++  */
    
/******************************************************************************
 Solution to Problem 705 - Maze
 by: Francisco Dibar
 date: Nov-28-2004
******************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <map>
//#define ONLINE_JUDGE 

#define DOT			'.'
#define SLASH		'/'
#define BSLASH		'\\'
#define WALL		'X'
#define PAINT		'#'

using namespace std;

////////////////////////////////////////////////////////////////////////////////
int floodfill(vector<vector<char> >& mat_maze, int xi, int yi)
// devuelve la cantidad de puntos pintados
// xi: fila inicial, yi: col inicial
{
	if (mat_maze[xi][yi] != DOT) return 0;

	queue<pair<int, int> > que_faltan;

	que_faltan.push(make_pair(xi, yi));
	int pintados = 0;
	while (!que_faltan.empty()) {
		pair<int, int> pos;
		pos = que_faltan.front();
		// puede ocurrir que apilo dos veces lo mismo
		que_faltan.pop();
		if (mat_maze[pos.first][pos.second] == DOT) {
			mat_maze[pos.first][pos.second] = PAINT;
			pintados++;
			if (pos.first-1 >= 0) {
				if (mat_maze[pos.first-1][pos.second] == DOT)
					que_faltan.push(make_pair(pos.first-1, pos.second));
			}
			if (pos.first+1 < mat_maze.size()) {
				if (mat_maze[pos.first+1][pos.second] == DOT)
					que_faltan.push(make_pair(pos.first+1, pos.second));
			}

			if (pos.second-1 >= 0) {
				if (mat_maze[pos.first][pos.second-1] == DOT)
					que_faltan.push(make_pair(pos.first, pos.second-1));
			}

			if (pos.second+1 < mat_maze[0].size()) {
				if (mat_maze[pos.first][pos.second+1] == DOT)
					que_faltan.push(make_pair(pos.first, pos.second+1));
			}
		}
	}
	return pintados;
}

////////////////////////////////////////////////////////////////////////////////
void maze_to_bmp(vector<vector<char> >& mat_maze, vector<vector<char> >& mat_mazebmp)
// transforma cada elemento de mat_maze en uno de 3x3 de mat_mazebmp
/*	/ en	..#		\ en	#..
			.#.				.#.
			#..				..#
*/
{
	int ancho = mat_maze[0].size()*3;
	for (int i = 0; i < (int)mat_maze.size(); i++) {
		mat_mazebmp[3*i  ].resize(ancho);
		mat_mazebmp[3*i+1].resize(ancho);
		mat_mazebmp[3*i+2].resize(ancho);
		for (int j = 0; j < (int)mat_maze[0].size(); j++) {
			if (mat_maze[i][j] == SLASH) {
				mat_mazebmp[3*i  ][3*j  ] = DOT;
				mat_mazebmp[3*i  ][3*j+1] = DOT;
				mat_mazebmp[3*i  ][3*j+2] = WALL;
				mat_mazebmp[3*i+1][3*j  ] = DOT;
				mat_mazebmp[3*i+1][3*j+1] = WALL;
				mat_mazebmp[3*i+1][3*j+2] = DOT;
				mat_mazebmp[3*i+2][3*j  ] = WALL;
				mat_mazebmp[3*i+2][3*j+1] = DOT;
				mat_mazebmp[3*i+2][3*j+2] = DOT;
			} else if (mat_maze[i][j] == BSLASH) {
				mat_mazebmp[3*i  ][3*j  ] = WALL;
				mat_mazebmp[3*i  ][3*j+1] = DOT;
				mat_mazebmp[3*i  ][3*j+2] = DOT;
				mat_mazebmp[3*i+1][3*j  ] = DOT;
				mat_mazebmp[3*i+1][3*j+1] = WALL;
				mat_mazebmp[3*i+1][3*j+2] = DOT;
				mat_mazebmp[3*i+2][3*j  ] = DOT;
				mat_mazebmp[3*i+2][3*j+1] = DOT;
				mat_mazebmp[3*i+2][3*j+2] = WALL;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
pair<int, int> solve_maze(vector<vector<char> >& mat_maze)
{
	vector<vector<char> > mat_mazebmp;
	mat_mazebmp.resize(mat_maze.size()*3);
	maze_to_bmp(mat_maze, mat_mazebmp);

	pair<int, int> sol;	// ciclos, longitud
	sol.first = 0;
	sol.second = 0;


	// comenzar a pintar desde los bordes, e ignorar los resultados
	// todo aquello que se pinta no es ciclo.
	// paredes verticales
	for (int i = 0; i < (int)mat_mazebmp.size(); i++) {
		floodfill(mat_mazebmp, i, 0);
		floodfill(mat_mazebmp, i, mat_mazebmp[0].size()-1);
	}
	// paredes horizontales (evito las esquinas inferiores pues ya las use en el ciclo anterior)
	for (int j = 1; j < (int)mat_mazebmp[0].size()-1; j++) {
		floodfill(mat_mazebmp, 0, j);
		floodfill(mat_mazebmp, mat_mazebmp.size()-1, j);
	}
	// comenzar a pintar desde cada punto con floodfill
	// si se pinta un recinto cerrado, entonces hay un ciclo
	// floodfill devuelve los puntos pintados, que hay que dividir por 3
	for (int i = 0; i < (int)mat_mazebmp.size(); i++) {
		for (int j = 0; j < (int)mat_mazebmp[0].size(); j++) {
			if (mat_mazebmp[i][j] == DOT) { 
				int longitud = floodfill(mat_mazebmp, i, j);
				if (longitud) {
					// hay un ciclo
					sol.first++;
					if (longitud > sol.second) sol.second = longitud;
				}
			}
		}
	}
	
	sol.second /= 3;
	return sol;
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

	vector<vector<char> > mat_maze;
	int ancho, 
		largo, 
		maze = 0;
	cin >> ancho >> largo;
	while (ancho && largo) {
		string str_line;
		maze++;
		mat_maze.resize(largo);
		for (int i = 0; i < largo; i++) {
			mat_maze[i].resize(ancho);
			cin >> str_line;
			for (int j = 0; j < ancho; j++)
				mat_maze[i][j] = str_line[j];
		}		
		pair<int, int> sol;
		sol = solve_maze(mat_maze);
		// mostrar salida
		cout << "Maze #" << maze << ":" << endl;
		if (!sol.first)
			cout << "There are no cycles." << endl << endl;
		else
			cout << sol.first << " Cycles; the longest has length " << sol.second << "." << endl << endl;
			
		cin >> ancho >> largo;
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

