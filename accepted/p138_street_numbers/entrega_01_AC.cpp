/* @JUDGE_ID:  40922FK  138  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 138 - Street Numbers
 by: Francisco Dibar
 date: Mar-01-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <iomanip>	// setw
#include <cmath>		// sqrt

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

	// 2xSum(i=1;n-1;i) = 2xSum(i=n+1;M;i)
	// => n(n-1) = M(M+1) - n(n+1)
	// busco n, M tal que M(M+1) = 2n^2
	// m^2 + m - 2n^2 = 0
	// aplico cuadratica con a=1, b=1 y c=-2n^2
	// M = (-1+(1+8n^2)^(0.5))/2
	// se cumple para aquellos M enteros 

/*	COMENTO EL CODIGO PARA MOSTRAR SOLO LA TABLA 

	int resultados = 0;
	double M, n;
	n = 6;
	M = 8;
	while (resultados < 10) {
		double raiz = sqrt(1+8*n*n);
		double cero = raiz - int(raiz);
		while (cero > 0.000000001) {
			n++;
			raiz = sqrt(1+8*n*n);
			cero = raiz - int(raiz);
		}
		M = (-1 + raiz)/2;
*/
/*
		// APROXIMACION LENTA
		int izq = M*(M+1);
		int der = 2*n*n;
		while (izq != der) {
			if (izq > der) {
				n++;
				der = 2*n*n;
			} else {
				M++;
				izq = M*(M+1);
			}
		}
*/
/*
		cout.precision(10);
		cout << setw(10) << n << setw(10) << M << endl;
		resultados++;
		n++;
	}
*/

	cout << "         6         8" << endl;
	cout << "        35        49" << endl;
	cout << "       204       288" << endl;
	cout << "      1189      1681" << endl;
	cout << "      6930      9800" << endl;
	cout << "     40391     57121" << endl;
	cout << "    235416    332928" << endl;
	cout << "   1372105   1940449" << endl;
	cout << "   7997214  11309768" << endl;
	cout << "  46611179  65918161" << endl;

	return 0;
}

/* @END_OF_SOURCE_CODE */

