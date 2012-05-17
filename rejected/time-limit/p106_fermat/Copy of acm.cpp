
/* @JUDGE_ID:  40922FK  106  C++  */
    
/******************************************************************************
 Solution to Problem 106 - Fermat vs. Pythagoras
 by: Francisco Dibar
 date: Jan-31-2004
******************************************************************************/

#include <iostream>
#include <math.h>
using namespace std;

#define MAX_N	1000000

#define MAX_TERNAS	3000000

#define X	0
#define Y	1
#define Z	2

int terna[MAX_TERNAS][3];

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
void init_terna()
{
	for (unsigned long i=0; i < MAX_TERNAS; i++) {
		terna[i][X] = 0;
		terna[i][Y] = 0;
		terna[i][Z] = 0;
	}
}

////////////////////////////////////////////////////////////////////////////////
void init_nros(int *vec, unsigned long n)
{
	for (unsigned long i=0; i < n; i++) 
		vec[i] = 0;
}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	unsigned long t = 0;	// cuenta las ternas encontradas
	unsigned long tp = 0;	// cuenta las ternas relativamente primas encontradas
	unsigned long n;		// nro leido
	unsigned long cn=0;	// cuenta los nros que no pertenecen a ninguna terna

	init_terna();
	scanf("%d",&n);
	int *vec_nros = new int[n];	// contiene los nros que aparecen en la terna
	if (!vec_nros) {
		// devolver error, no hay memoria suficiente
		cerr << "memoria insuficiente" << endl;
		return -1;
	}
	init_nros(vec_nros, n);
	for (unsigned long z=5; z <= n; z++) {	// empieza en z=5 porque la primera terna es (3,4,5)
//		double z2 = z*z;
		for (unsigned long x=z-1; x >= unsigned long(z/2); x--) {
//			double x2 = x*x;
			double y = sqrt(z*z - x*x);
			double yb = double(int(y));
			if ((y == yb) && (unsigned long(y) <= x)) {		// evito los pares (x,y) e (y,x)
//				double y2 = y*y;
//				if ((x2 + y2) == z2) {
					terna[t][X] = x;
					terna[t][Y] = y;
					terna[t][Z] = z;
					// mostrar las ternas
					// si vec_nros[i] = 1 entonces i aparece en alguna terna
					vec_nros[x-1] = 1;
					vec_nros[unsigned long(y)-1] = 1;
					vec_nros[z-1] = 1;
					printf("%d : (%d,%d,%d)\n",t+1, terna[t][X], terna[t][Y], terna[t][Z]);
					t++;
					if (relat_primos(x,y,z))
						tp++;
//				}
			}
		}
	}
	
	// cuento la cantidad de nros distintos que aparecen en las ternas
	for (unsigned long i=0; i < n; i++) {
		cn += vec_nros[i];
	}
	cn = n - cn;	// obtengo los nros distintos que no aparecen en ninguna terna

	// mostrar el resultado
	printf("relativamente primos : %d\n",tp);
	printf("nros que no pertenecen a ninguna terna : %d\n",cn);

	delete []vec_nros;
	return 0;
}

