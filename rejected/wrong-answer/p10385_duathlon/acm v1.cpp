/* @JUDGE_ID:  40922FK  10385  C++  */
    
/**************************************************************************
 Solution to Problem 10385 - Duathlon
 by: Francisco Dibar
 date: Dec-01-2004
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#include <fstream>
#include <vector>
//#define ONLINE_JUDGE 

#define R	0 
#define K	1 

using namespace std;

///////////////////////////////////////////////////////////////////////////
bool cheater_wins(int dist, vector<vector<double> >& mat_datos, double *t, double *r)
{
	*t = *r = 0;
	double h = 0.01;
	int competidores = mat_datos.size();
	int ptos = (int)(double)dist / h;
	vector<vector<double> > mat_eval(competidores);
	
	// evaluar los tiempos de cada competidor en funcion de r
	for (int i = 0; i < competidores; ++i) {
		mat_eval[i].resize(ptos);
		for (int j = 0; j < ptos; ++j) {
			double r = h*j;
			mat_eval[i][j] = r / mat_datos[i][R] + (dist - r) / mat_datos[i][K];
		}
	}
/*
	// mostrar
	for (int i = 0; i < competidores; ++i) {
		for (int j = 0; j < ptos; ++j) {
			cout.precision(2);
			cout << mat_eval[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
*/
	// ver si el ultimo competidor puede ganar para algun r
	for (int i = 0; i < ptos; ++i) {
		bool menor_t = true;
		double menor_diferencia = mat_eval[competidores-1][i];
		for (int j = 0; (j < competidores-1) && menor_t; ++j) {
			if (mat_eval[competidores-1][i] >= mat_eval[j][i]) 
				menor_t = false;
			else if (mat_eval[j][i] - mat_eval[competidores-1][i] < menor_diferencia) 
				menor_diferencia = mat_eval[j][i] - mat_eval[competidores-1][i];
		}
		if (menor_t) {
			if (*t < menor_diferencia) {
				*t = menor_diferencia;
				*r = h*i;
			}
		}
	}
	if (*t) 
		return true;
	else
		return false;
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

	int total_dist;
	cin >> total_dist;
	while (!cin.eof()) {
		int competidores;
		cin >> competidores;
		vector<vector<double> > mat_datos(competidores);
		for (int i = 0; i < competidores; ++i) {
			mat_datos[i].resize(2);
			cin >> mat_datos[i][R] >> mat_datos[i][K];
		}
		double t, r;
		if (cheater_wins(total_dist, mat_datos, &t, &r)) {
			cout.setf(ios::fixed);
			cout.precision(0);
			cout << "The cheater can win by " << t*3600 << " seconds with r = ";
			cout.precision(2);
			cout << r << "km and k = " << total_dist - r << "km." << endl;
		} else
			cout << "The cheater cannot win." << endl;
		// puede haber o no una linea en blanco entre dos carreras
		cin >> total_dist;
		if (!total_dist) cin >> total_dist;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

