
/* @JUDGE_ID:  40922FK  136  C++  */
    
/******************************************************************************
 Solution to Problem 136 - Ugly Numbers
 by: Francisco Dibar
 date: Jan-24-2004
******************************************************************************/

/******************************************************************************
 Metodo de resolucion:

 para cada nro de 1 en adelante, busco su maximo comun divisor que sea primo,
 si ese mcd es mayor que 5 entonces el nro no es ugly, si en cambio es 2 o 3 o 5
 si lo es.

******************************************************************************/

#include <iostream>
#include "primos.h"
using namespace std;

#define ORDEN_BUSCADO	1500

////////////////////////////////////////////////////////////////////////////////
bool esPrimo_Grande(__int64 n)
{
	// los nros pares mayores que 2 no son primos
//	if ((n % 2 == 0) && (n > 2)) 
//		return false;
	
	// impar x impar = impar
	// primo => impar
	// entonces un mcd de un primo ha de ser impar
	for (__int64 i = 2; i <= (n/2); i++) {
		__int64 m = __int64(n/i);
		if ((n % m == 0) && (m > 1)) {
			return false;
		}
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////
bool esPrimo(__int64 n)
{
	// los nros pares mayores que 2 no son primos
	if ((n % 2 == 0) && (n > 2)) 
		return false;

	if (n > MAX_PRIMO)
		return esPrimo_Grande(n);

	// buscar n en el vector primos mediante busqueda binaria	
	int i = 0;
	int j = CANT_PRIMOS;
	int p = (i + j) / 2;

	while ((i <= j) && (n != primos[p])) {
		if (n < primos[p])
			j = p - 1;
		else
			i = p + 1;
		p = (i + j) / 2;
	}
	
	if (n != primos[p])		
		return false;		// no lo encontro
	else 
		return true;

}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{

	// los primeros 3 ugly numbers son 1, 2, 3, 4 y 5 (empiezo de aca para evitar la pregunta si el nro es menor a 2, 3 o 5)
	__int64 u = 1;	// cuenta los ugly encontrados (el 1 es ugly por convencion)
	__int64 n = 1;	// nro a determinar si es ugly

	char su[20];
	char sn[20];
	while (u < ORDEN_BUSCADO) {
		n++;
		bool ugly = false;
		// si no es divisible por 2, 3 o 5 entonces no es ugly
		if ((n % 2 == 0) || (n % 3 == 0) || (n % 5 == 0)) {
			for (__int64 i = 1; !ugly && (i <= (n/2)); i++)	{
				__int64 m = __int64(n/i);
				if ((n % m == 0) && esPrimo(m)) {
					if ((m == 2) || (m == 3) || (m == 5)) {
						ugly = true;
					} else 
						break;	// evita los casos con mcd 2 o 3 o 5 y uno mayor
				}
			}
		} else
			ugly = false;
		if (ugly) {
			u++;
			ugly = false;
			_i64toa(n,sn,10);
			_i64toa(u,su,10);
			cout << su << "\t" << sn << endl;		// QUITAR!!
		}
	}
	_i64toa(n,sn,10);
	cout << "The " << ORDEN_BUSCADO << "'th ugly number is " << sn;

	return 0;
}

