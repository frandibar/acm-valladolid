
/* @JUDGE_ID:  40922FK  106  C++  */
    
/******************************************************************************
 Solution to Problem 106 - Fermat vs. Pythagoras
 by: Francisco Dibar
 date: Mar-09-2004
******************************************************************************/

#include <iostream>
#include <queue>
#include <list>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAX_N		1000000

////////////////////////////////////////////////////////////////////////////////
unsigned long gcd(unsigned long u,unsigned long v)
// devuelve el maximo comun divisor entre u y v
{
	unsigned long t;
	while (v != 0) {
		t = u % v; 
		u = v;
		v = t;
	}
	return u;
}

////////////////////////////////////////////////////////////////////////////////
bool relat_primos(unsigned long x, unsigned long y, unsigned long z)
// devuelve true si x, y y z no tienen divisores comunes
{
	return !((gcd(x,y) != 1) || (gcd(x,z) != 1) || (gcd(y,z) != 1));
}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	unsigned long n;		// nro leido
	queue<unsigned long> que_input;		// cola para guardar input
	cin >> n;
	// leer la entrada y guardarla en lst_input
	while (n && (n <= MAX_N) && !cin.eof()) {
		que_input.push(n);
		cin >> n;
	}

	while (!que_input.empty()) {
		unsigned long t = 0;	// cuenta las ternas encontradas
		unsigned long tp = 0;	// cuenta las ternas relativamente primas encontradas
		unsigned long cn = 0;	// cuenta los nros que no pertenecen a ninguna terna

		n = que_input.front();
		que_input.pop();	// descartar el valor recien leido
		list<unsigned long> lst_nros_terna;		// lista para guardar los nros que aparecen en la terna

		for (unsigned long z=5; z <= n; z++) {	// empieza en z=5 porque la primera terna es (3,4,5)
			for (unsigned long x=z-1; x >= (unsigned long)(z/2); x--) {
				double y = sqrt(z*z - x*x);
				double yb = double(int(y));
				if ((y == yb) && ((unsigned long)y <= x)) {		// evito los pares (x,y) e (y,x)
					// agregar los nros de la terna a la lista
					lst_nros_terna.push_back(x);
					lst_nros_terna.push_back((unsigned long)y);
					lst_nros_terna.push_back(z);
					t++;
					if (relat_primos(x,(unsigned long)y,z))
						tp++;
				}
			}
		}

		// obtener las lista de nros ternados sin repetidos, para poder calcular cn
		lst_nros_terna.sort();
		list<unsigned long>::iterator LI = unique(lst_nros_terna.begin(), lst_nros_terna.end());
		lst_nros_terna.erase(LI, lst_nros_terna.end());
		cn = n - lst_nros_terna.size();
		// mostrar el resultado
		cout << tp << ' ' << cn << endl;
	}
	return 0;
}

