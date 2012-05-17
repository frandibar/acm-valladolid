/* @JUDGE_ID:  40922FK  10385  C++  */
    
/**************************************************************************
 Solution to Problem 10385 - Duathlon
 by: Francisco Dibar
 date: Dec-06-2004
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
bool cheater_wins(int dist, vector<vector<double> >& mat_datos, 
						double *t, double *r)
{
	*t = *r = 0;
	double h = 0.01;
	int competidores = mat_datos.size(),
		cheater = competidores - 1,
		ptos = int(double(dist) / h);
	vector<vector<double> > mat_eval(competidores);
	
	// reservar espacio para la matriz
	for (int i = 0; i < competidores; ++i) 
		mat_eval[i].resize(ptos);

	// evaluar los tiempos de cada competidor en funcion de r
	// evaluo de a un punto para todos los competidores
	for (int j = 0; j < ptos; ++j) {
		bool menor_t = true;
		double rj = h*j;
		mat_eval[cheater][j] = rj / mat_datos[cheater][R] 
									+ (dist - rj) / mat_datos[cheater][K];
		double menor_diferencia = mat_eval[cheater][j];
		for (int i = cheater-1; (i >= 0) && menor_t; --i) {
			mat_eval[i][j] = rj / mat_datos[i][R] 
								+ (dist - rj) / mat_datos[i][K];

			if (mat_eval[cheater][j] >= mat_eval[i][j]) 
				menor_t = false;
			else 
				if (mat_eval[i][j] - mat_eval[cheater][j] < menor_diferencia) 
					menor_diferencia = mat_eval[i][j] - mat_eval[cheater][j];
		}
		if (menor_t && (*t < menor_diferencia)) {
			*t = menor_diferencia;
			*r = h*j;
		}
	}
	return (*t);
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
			cout << "The cheater can win by " 
					<< t*3600 << " seconds with r = ";
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

