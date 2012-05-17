/* @JUDGE_ID:  40922FK  10310  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10310 - Dog and Gopher
 by: Francisco Dibar
 date: Nov-06-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 

using namespace std;

///////////////////////////////////////////////////////////////////////////
double square_distance(double x0, double y0, double x1, double y1)
{
	return ((y1 - y0)*(y1 - y0) + (x1 - x0)*(x1 - x0));
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

	// setear la precision de salida
	cout.setf(ios::fixed);
	cout.precision(3);

	int holes;	// cantidad de agujeros
	cin >> holes;	

	while (!cin.eof()) {
		double xd, yd, xg, yg, xh, yh;
		double xhole, yhole;		// posicion del agujero de escape
		// leer la posicion del gopher y del dog
		cin >> xg >> yg >> xd >> yd;
		bool escapa = false;
		// para cada agujero
		for (int h = 0; h < holes; h++) {
			// leer la posicion del agujero
			cin >> xh >> yh;
			// si escapa debo seguir leyendo los agujeros
			// pero los ignoro.
			if (!escapa) {
				// calcular la distancia del gopher al agujero
				double dist_gopher, dist_dog;
				dist_gopher = square_distance(xg, yg, xh, yh);
				dist_dog = square_distance(xd, yd, xh, yh);
				// calcular la distancia del dog al agujero
				// si mas del doble de la anterior, entonces el gopher escapa
				if (dist_dog >= 4 * dist_gopher) {	// 4 xq es la dist al cuadrado
					escapa = true;
					xhole = xh;
					yhole = yh;
				}
			}
		}
		if (!escapa) 
			cout << "The gopher cannot escape." << endl;
		else 
			cout << "The gopher can escape through the hole at (" 
					<< xhole << "," << yhole << ")." << endl;

		// READ NEXT INPUT
		cin >> holes;	
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

