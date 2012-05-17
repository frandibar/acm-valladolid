/* @JUDGE_ID:  40922FK  408  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 408 - Uniform Generator
 by: Francisco Dibar
 date: Mar-21-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 

#include <vector>
#include <iomanip>		// setw

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

	int step, mod;
	cin >> step >> mod;
	while (!cin.eof()) {
		vector<bool> vec_gen(mod);		// se inicializa en false
		int generados = 0;
		int s = 0;
		for (int i = 0; i < mod; i++) {
			s = (s + step) % mod;
			if (!vec_gen[s]) {
				vec_gen[s] = true;
				generados++;
			} else
				// se repitio un nro -> alguno no va a ser generado
				break;
		}
		// mostrar la salida
		cout << setw(10) << step 
				<< setw(10) << mod 
				<< "    "
				<< (generados == mod ? "Good" : "Bad") << " Choice" << endl;

		cin >> step >> mod;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

