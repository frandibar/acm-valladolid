/* @JUDGE_ID:  40922FK  10094  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10094 - Place the Guards
 by: Francisco Dibar
 date: Mar-03-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>

//#define DEBUG
using namespace std;

///////////////////////////////////////////////////////////////////////////
int candidatos(vector<int> &vec_candidatos, 
					 vector<bool> &vec_filas,
					 vector<bool> &vec_cols,
					 vector<bool> &vec_diags,
					 vector<bool> &vec_antidiags, int n, int y)
// devuelve vec_candidatos con las filas en las que se puede colocar, 
// para la columna y
{
	int cant = 0;
	// buscar las combinaciones de diagonales y antidiagonales
	for (int x = 0; x < n; x++) {
      int d = x + y;
		int a = x - y + n - 1;
		if (!vec_diags[d] && !vec_antidiags[a] && 
			 !vec_filas[x] && !vec_cols[y]) {
			// posicion a salvo
			vec_candidatos[cant] = x;
			cant++;
		}
	}
	return cant;
}

///////////////////////////////////////////////////////////////////////////
#ifdef DEBUG
void nqueens(vector<int> &vec_sol, 
				vector<bool> vec_filas, vector<bool> vec_cols, 
				vector<bool> vec_diags, vector<bool> vec_antidiags, 
				int colocados, int n, bool *fin, 
				vector< vector<bool> > mat_tablero)
#else
void nqueens(vector<int> &vec_sol, 
				vector<bool> vec_filas, vector<bool> vec_cols, 
				vector<bool> vec_diags, vector<bool> vec_antidiags, 
				int colocados, int n, bool *fin)
#endif
{
	if (colocados == n) {
		*fin = true;

		#ifdef DEBUG
			// mostrar el tablero
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++)
  					cout << mat_tablero[i][j] << " ";
				cout << endl;
			} 
			cout << endl;
		#endif

	} else {
		// buscar posiciones posibles
		vector<int> vec_candidatos(n);	// hay a lo sumo n candidatos
		int cant_candidatos = candidatos(vec_candidatos, vec_filas, vec_cols, 
										vec_diags, vec_antidiags, n, colocados);

		for (int i = 0; i < cant_candidatos && !(*fin); i++) {

			int d = vec_candidatos[i] + colocados;
			int a = vec_candidatos[i] - colocados + n - 1;
			
			bool old_f = vec_filas[vec_candidatos[i]];
			bool old_c = vec_cols[colocados];
			bool old_d = vec_diags[d];
			bool old_a = vec_antidiags[a];
			
			vec_filas[vec_candidatos[i]] = true;
			vec_cols[colocados] = true;
			vec_diags[d] = true;
			vec_antidiags[a] = true;
			
			// incremento porque indice empieza en 1
			vec_sol[colocados] = vec_candidatos[i]+1;		

			#ifdef DEBUG
				// mostrar vec_sol
				for (int j = 0; j <= colocados; j++)
					cout << vec_sol[j] << " ";
				cout << endl;
			#endif		

			#ifdef DEBUG
				mat_tablero[vec_candidatos[i]][colocados] = true;
				nqueens(vec_sol, vec_filas, vec_cols, vec_diags, vec_antidiags, 
							colocados+1, n, fin, mat_tablero);
				mat_tablero[vec_candidatos[i]][colocados] = false;
			#else
				nqueens(vec_sol, vec_filas, vec_cols, vec_diags, vec_antidiags, 
							colocados+1, n, fin);
			#endif		
			
			// restauro los valores originales
			vec_filas[vec_candidatos[i]] = old_f;
			vec_cols[colocados] = old_c;
			vec_diags[d] = old_d;
			vec_antidiags[a] = old_a;
		}
	}
}	

///////////////////////////////////////////////////////////////////////////
bool hay_solucion(int n, vector<int> &vec_sol)
// devuelve la cantidad de posibles formas de colocar n reinas 
// en un tablero de nxn
{
	int diags = 2*n-1;
	
	#ifdef DEBUG
		vector< vector<bool> > mat_tablero(n);
		for (int i = 0; i < n; i++)
		mat_tablero[i].resize(n);
	#endif 

	vector<bool> vec_filas(n);
	vector<bool> vec_cols(n);
	vector<bool> vec_diags(diags);
	vector<bool> vec_antidiags(diags);
	bool fin = false;
	#ifdef DEBUG
		nqueens(vec_sol, vec_filas, vec_cols, vec_diags, vec_antidiags, 0, 
					n, &fin, mat_tablero);
	#else
		nqueens(vec_sol, vec_filas, vec_cols, vec_diags, vec_antidiags, 0, 
					n, &fin);
	#endif 
	
	return fin;
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

	int n;
	cin >> n;					// 1 < n < 1001
	while (!cin.eof()) {				
		vector<int> vec_sol(n);		// vector para almacenar la solucion
		
		// resolver
		if (hay_solucion(n, vec_sol)) {				
			// mostrar la salida
			for (int i = 0; i < n-1; i++)
				cout << vec_sol[i] << " ";
			cout << vec_sol[n-1] << endl;
		} else
			cout << "Impossible" << endl;

		// leer el proximo caso
		cin >> n;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

