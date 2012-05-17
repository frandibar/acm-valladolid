/* @JUDGE_ID:  40922FK  10116  C++  */
    
/**************************************************************************
 Solution to Problem 10116 - Robot Motion
 by: Francisco Dibar
 date: Dec-29-2004
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>

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

	int rows, cols, coli;
	cin >> rows >> cols >> coli;
	while ((rows || cols || coli) && !cin.eof()) {
		vector<vector<char> > mat_grid(rows);
		vector<vector<int> > mat_path(rows);
		
		// leer la matriz de direcciones
		for (int i = 0; i < rows; i++) {
			mat_grid[i].resize(cols);
			mat_path[i].resize(cols);
			for (int j = 0; j < cols; j++)  
				cin >> mat_grid[i][j];
		}
		
		// resolver el camino
		bool loop = false;
		int steps = 1, looplen = 0;
		int r = 0,
			 c = coli - 1;
		mat_path[r][c] = steps;
		// continuar mientras no entra en loop o no sale de la grilla
		while (!loop && ((r >= 0) && (r < rows) && (c >= 0) && (c < cols))) {
			switch (mat_grid[r][c]) {
				case 'N':	r--; break;
				case 'S':	r++; break;
				case 'E':	c++; break;
				case 'W':	c--; break;
			}
			if ((r >= 0) && (r < rows) && (c >= 0) && (c < cols)) {
				if (mat_path[r][c]) {
					// hay loop
					loop = true;
					looplen = steps - mat_path[r][c] + 1;
					steps = mat_path[r][c] - 1;
				} else
					mat_path[r][c] = ++steps;	// incremento y asigno
			} 
		}

		// mostrar la salida
		if (!loop)
			cout << steps << " step(s) to exit" << endl;
		else
			cout << steps << " step(s) before a loop of " << looplen << " step(s)" << endl;

		cin >> rows >> cols >> coli;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

