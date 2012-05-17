/* @JUDGE_ID:  40922FK  10037  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10037 - Bridge
 by: Francisco Dibar
 date: Aug-18-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <algorithm>		// sort

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

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

	int cases;
	cin >> cases;

	for (int k = 0; k < cases; k++) {

		// READ INPUT
		int persons;
		cin >> persons;
		vector<int> vec(persons);
		for (int i = 0; i < persons; i++)
			cin >> vec[i];

		// PROCESS
		sort(vec.begin(), vec.end());
		// calculate time
		int time = 0;
		int m, n;
		if (persons == 1)
			time = vec[0];
		else if (persons == 2)
			time = vec[0] + vec[1];
		else if (persons > 2) {
			int trips = 2 * persons - 3;
			if (persons % 2 == 0) { 	// even
				m = trips / 4;
				n = 2 * m + 1;
			} else {
				m = trips / 4 + 1;
				n = 2 * (trips / 4) + 1;
			}
			time = m * vec[0] + n * vec[1];
			for (int i = persons-1; i > 1; i -= 2)
				time += vec[i];
		}

		// SHOW OUTPUT
		cout << time << endl;
		// show trips
		if (persons == 0)
			cout << endl;
		else if (persons == 1)
			cout << vec[0] << endl;
		else {
			int i;
			for (i = persons-1; i > 2; i -= 2) {
				cout << vec[0] << " " << vec[1] << endl;
				cout << vec[0] << endl;
				cout << vec[i-1] << " " << vec[i] << endl;
				cout << vec[1] << endl;
			}
			if (persons % 2 == 0) 	// even
				cout << vec[0] << " " << vec[1] << endl;
			else {
				cout << vec[0] << " " << vec[1] << endl;
				cout << vec[0] << endl;
				cout << vec[0] << " " << vec[i] << endl;
			}
		}

		if (k < cases-1)
			cout << endl;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

/* el esquema siempre es el siguiente
 
	viajes = 2xn - 3 con n la cantidad de personas
	tiempo = Mxa + Nxb + v[n-2k] + .. + v[n-2] + v[n]

	si viajes es par
		M = viajes / 4		(/ division entera)
		N = 2xM + 1
	sino
		M = viajes / 4	+ 1	(/ division entera)
		N = 2x(viajes / 4) + 1

	sea a <= b <= c <= d <= e
	tiempo = 2a + 3b + c + e

	-> a b	(menores)
	<- a
	-> d e	(mayores)
	<- b
	-------	(se repite el patron anterior)
	-> a b	(pares terminan aca)
	<- a
	-> a c	(impares terminan aca)

	
*/

