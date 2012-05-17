/* @JUDGE_ID:  40922FK  861  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 861 - Little Bishops
 by: Francisco Dibar
 date: Feb-19-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>

using namespace std;

///////////////////////////////////////////////////////////////////////////
class point {
public:
	int x, y;
	point(int cx = 0, int cy = 0) { x = cx; y = cy; }
};

///////////////////////////////////////////////////////////////////////////
void candidatos(vector<point> &vec_candidatos, 
								  vector<bool> &vec_diags,
								  vector<bool> &vec_antidiags, int *cant, int n, int x, int y)
// devuelve vec_candidatos con las coordenadas (diag, antidiag) 
// de las posibles ubicaciones en el tablero, y la cantidad en cant
{
	// buscar las combinaciones de diagonales y antidiagonales
	for (int k = x*n+y; k < n*n; k++) {
      int xn = k / n;
      int yn = k % n;   
      int d = xn + yn;
		int a = xn - yn + n - 1;
		if (!vec_diags[d] && !vec_antidiags[a]) {
			// posicion a salvo
			(*cant)++;
			point pto(xn, yn);
			vec_candidatos.push_back(pto);
		}
	}
}

///////////////////////////////////////////////////////////////////////////
void nbishops(vector<bool> vec_diags, vector<bool> vec_antidiags, 
				  int colocados, int limite, long *soluciones, int n, 
                int x, int y)
//// debug
//void nbishops(vector<bool> vec_diags, vector<bool> vec_antidiags, 
//				  int colocados, int limite, long *soluciones, int n, 
//                  int x, int y, vector< vector<bool> > mat_tablero)
//// fin debug
{
	if (colocados == limite) {
		(*soluciones)++;
/*
		// debug - mostrar el tablero
      cout << "solucion " << *soluciones << endl;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
  				cout << mat_tablero[i][j] << " ";
			cout << endl;
		} 
		cout << endl;

		for (int i = 0; i < 2*n-1; i++) {
			cout << vec_diags[i] << " ";
			cout << vec_antidiags[i] << endl;
		}	// antidiags[1] deberia ser 0!!
		cout << endl;
		// fin debug 
*/	} else {
		colocados++;
		// buscar posiciones posibles
		vector<point> vec_candidatos;
		int cant_candidatos = 0;
		candidatos(vec_candidatos, vec_diags, vec_antidiags, &cant_candidatos, n, x, y);

		// debug
		//cout << "colocados: " << colocados-1 << " candidatos: " << cant_candidatos << endl;
		for (int i = 0; i < cant_candidatos; i++) {
			int d = vec_candidatos[i].x + vec_candidatos[i].y;
			int a = vec_candidatos[i].x - vec_candidatos[i].y + n - 1;
			bool old_d = vec_diags[d];
			bool old_a = vec_antidiags[a];
			vec_diags[d] = true;
			vec_antidiags[a] = true;
			
			//// debug
			//mat_tablero[vec_candidatos[i].x][vec_candidatos[i].y] = true;
			//// fin debug

			nbishops(vec_diags, vec_antidiags, colocados, limite, soluciones, n, vec_candidatos[i].x, vec_candidatos[i].y);
			
			//// debug
			//nbishops(vec_diags, vec_antidiags, colocados, limite, soluciones, n, vec_candidatos[i].x, vec_candidatos[i].y, mat_tablero);
			//mat_tablero[vec_candidatos[i].x][vec_candidatos[i].y] = false;
			//// fin debug
			
			// restauro el valor original
			vec_diags[d] = old_d;
			vec_antidiags[a] = old_a;
		}
	}
}	

///////////////////////////////////////////////////////////////////////////
long soluciones(int n, int cant_alfiles)
// devuelve la cantidad de posibles formas de colocar cant_alfiles 
// alfiles en un tablero de nxn
{
	int diags = 2*n-1;
	
	//// debug
	//vector< vector<bool> > mat_tablero(n);
	//for (int i = 0; i < n; i++)
	//	mat_tablero[i].resize(n);
	//// fin debug

	vector<bool> vec_diags(diags);
	vector<bool> vec_antidiags(diags);
	long soluciones = 0;
	nbishops(vec_diags, vec_antidiags, 0, cant_alfiles, &soluciones, n, 0, 0);

	//// debug
	//nbishops(vec_diags, vec_antidiags, 0, cant_alfiles, &soluciones, n, 0, 0, mat_tablero);

	return soluciones;
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

	int n, k;
	cin >> n >> k;
	while ((n || k) && !cin.eof()) {		
		// asumo que la respuesta para n=1 k=0 es 1
		cout << soluciones(n, k) << endl;
		cin >> n >> k;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

