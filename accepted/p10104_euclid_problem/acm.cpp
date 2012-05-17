/* @JUDGE_ID:  40922FK  10104  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10104 - Euclid Problem
 by: Francisco Dibar
 date: Oct-26-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <cmath>

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

using namespace std;

// REVISAR: buscar una solucion iterativa para mejorar velocidad
///////////////////////////////////////////////////////////////////////////
long gcd(long p, long q, long *x, long *y)
{
	if (q > p) 
		return gcd(q, p, y, x);

	if (q == 0) {
		*x = 1;
		*y = 0;
		return p;
	}

	long x1, y1, g;
	g = gcd(q, p%q, &x1, &y1);
	*x = y1;
	*y = (x1 - floor(p/q) * y1);
	return g;
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

	long a, b;
	cin >> a >> b;
	while (!cin.eof()) {
		long x, y, g;
		// PROCESS
		g = gcd(a, b, &x, &y);

		// SHOW OUTPUT
		cout << x << " " << y << " " << g << endl;

		// READ INPUT
		cin >> a >> b;
	}

#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

