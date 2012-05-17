
/* @JUDGE_ID:  40922FK  488  C++  */
    
/******************************************************************************
 Solution to Problem 488 - Triangle Wave
 by: Francisco Dibar
 date: May-11-2004
******************************************************************************/

#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	int amp, frec;

	cin >> amp >> frec;

	for (int f = 0; f < frec; f++) {
		int a;
		for (a = 0; a < amp; a++) {
			for (int h = 1; h <= a; h++) {
				cout << a;
			}
			cout << endl;
		}
		for (a = amp; a > 0; a--) {
			for (int h = a; h > 0; h--) {
				cout << a;
			}
			if (a > 1) cout << endl;	// evitar 2 lineas entre 2 crestas
		}
		if (f < frec-1) cout << endl;		// evitar nueva linea al final de todo
	}
	return 0;
}

