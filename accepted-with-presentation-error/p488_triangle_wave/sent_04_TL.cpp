
/* @JUDGE_ID:  40922FK  488  C++  */
    
/******************************************************************************
 Solution to Problem 488 - Triangle Wave
 by: Francisco Dibar
 date: May-28-2004
******************************************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
//#define ONLINE_JUDGE 

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	ostringstream os_output;
	int casos;
	cin >> casos;

	for (int i = 0; i < casos; i++) {

		int amp, frec;
		cin >> amp >> frec;

		for (int f = 0; f < frec; f++) {
			int a;
			for (a = 0; a < amp; a++) {
				int h;
				for (h = 0; h < a; h++) {
					os_output << a;
				}
				if (h > 0) os_output << endl;	// con la condicion evito la primera linea
			}
			for (a = amp; a > 0; a--) {
				for (int k = a; k > 0; k--) {
					os_output << a;
				}
				os_output << endl;
			}
			if (f < frec-1) os_output << endl;		// evitar nueva linea al final de todo
		}
		if (i < casos-1) os_output << endl;
	}
	cout << os_output.str();
	return 0;
}

