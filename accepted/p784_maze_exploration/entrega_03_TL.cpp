/* @JUDGE_ID:  40922FK  784  C++  */
    
/******************************************************************************
 Solution to Problem 784 - Maze Exploration
 by: Francisco Dibar
 date: Nov-25-2004
******************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <map>
//#define ONLINE_JUDGE 

#define MAX_LINES		30
#define MAX_LEN		80

#define WALL			'X'
#define START			'*'
#define PAINT			'#'
#define SEP				'_'
#define EMPTY			' '

#define SEPARATOR		"_____"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
void floodfill(vector<vector<char> >& mat_maze, int xi, int yi)
// xi: fila inicial, yi: col inicial
{
	queue<pair<int, int> > que_faltan;

	que_faltan.push(make_pair(xi, yi));
	while (!que_faltan.empty()) {
		pair<int, int> pos;
		pos = que_faltan.front();
		mat_maze[pos.first][pos.second] = PAINT;
		que_faltan.pop();
		if ((mat_maze[pos.first-1][pos.second] != WALL) && 
			 (mat_maze[pos.first-1][pos.second] != SEP) && 
			 (mat_maze[pos.first-1][pos.second] != PAINT))
			que_faltan.push(make_pair(pos.first-1, pos.second));

		if ((mat_maze[pos.first+1][pos.second] != WALL) && 
			 (mat_maze[pos.first+1][pos.second] != SEP) && 
			 (mat_maze[pos.first+1][pos.second] != PAINT))
			que_faltan.push(make_pair(pos.first+1, pos.second));

		if ((mat_maze[pos.first][pos.second-1] != WALL) && 
			 (mat_maze[pos.first][pos.second-1] != SEP) && 
			 (mat_maze[pos.first][pos.second-1] != PAINT))
			que_faltan.push(make_pair(pos.first, pos.second-1));

		if ((mat_maze[pos.first][pos.second+1] != WALL) && 
			 (mat_maze[pos.first][pos.second+1] != SEP) && 
			 (mat_maze[pos.first][pos.second+1] != PAINT))
			que_faltan.push(make_pair(pos.first, pos.second+1));
	}
}

////////////////////////////////////////////////////////////////////////////////
void mostrar(vector<vector<char> >& mat_maze, int row)
{
	for (int i = 0; i < row; i++) {
		string str_line = "";
		int largo = 0;
		for (int j = 0; j < mat_maze[i].size(); j++) {
			if (mat_maze[i][j] == WALL) largo = j;
			str_line += mat_maze[i][j];
		}
		cout << str_line.substr(0, largo+1) << endl;
	}
	cout << SEPARATOR << endl;
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

	int cant_mazes;
	// leer la cantidad de laberintos
	cin >> cant_mazes;
	string str_line;
	getline(cin, str_line);

	// resolver cada laberinto
	for (int i = 0; i < cant_mazes; i++) {
		vector<vector<char> > mat_maze;
		mat_maze.resize(MAX_LINES);
		getline(cin, str_line);
		int row = 0;	// guarda la cantidad de filas del maze
		int xi, yi;		// guardan la posicion inicial
		while ((str_line[0] != SEP) && (row < MAX_LINES)) {
			// leer el laberinto y cargarlo en mat_maze
			mat_maze[row].resize(MAX_LEN);
			// cargar la fila
			for (int j = 0; j < str_line.length(); j++) {
				mat_maze[row][j] = str_line[j];
				if (str_line[j] == START) {
					xi = row;
					yi = j;
				}
			}
			getline(cin, str_line);
			row++;
		}
		floodfill(mat_maze, xi, yi);
		mostrar(mat_maze, row);
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

