
/* @JUDGE_ID:  40922FK  100  C++  */
    
/******************************************************************************
 Solution to Problem 100 - The 3n + 1 problem
 by: Francisco Dibar
 date: Mar-03-2004
******************************************************************************/

#include <iostream>
#include <algorithm>
#include <list>

#define LIMITE_INF 0
#define LIMITE_SUP 1000000

using namespace std;

struct resultado { 
	int i, j, k; 
};

/****************************************************************************/
void imprimir_res(resultado& res)
{
	cout << res.i << " " << res.j << " " << res.k << endl;
}

/****************************************************************************/
int ciclos(int i)
{
	int cic = 1;
	while (i != 1) {
		if ((i % 2) == 0)	// si es par
			i = i/2;
		else
			i = 3*i+1;
		cic++;
	}
	return cic;
}

/*****************************************************************************
*	PROGRAMA PRINCIPAL
******************************************************************************/
int main(int argc, char* argv[])
{
	list<resultado> salida;
	int i, j;
	cin >> i >> j;

	while (i && j) {
		// verificar que no se exceda el limite permitido
		if ((i <= LIMITE_INF) || (i >= LIMITE_SUP) || (j <= LIMITE_INF) || (j >= LIMITE_SUP)) {
			cerr << "Error por limite excedido (0 - 1000000)";
			return -1;
		}
		int a, b;
		if (i <= j) {
			a = i; b = j;
		} else {
			a = j; b = i;
		}
		int max = 0;
		int aux;
		while (a <= b) {
			aux = ciclos(a);
			if (aux > max) max = aux;
			a++;
		}
		resultado res;
		res.i = i; res.j = j; res.k = max;
		salida.push_back(res);
		i=j=0;
		cin >> i >> j;
	}
	// mostrar los resultados
	for_each(salida.begin(), salida.end(), imprimir_res);
	return 0;
}
