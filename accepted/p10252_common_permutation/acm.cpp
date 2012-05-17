/* @JUDGE_ID:  40922FK  10252  C++  */
    
/**************************************************************************
 Solution to Problem 10252 - Common Permutation
 by: Francisco Dibar
 date: Feb-06-2005
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>
#include <algorithm>		// sort

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

	string p1, p2;
	
	getline(cin, p1);
	getline(cin, p2);
	while (!cin.eof()) {
		string common;
		// ordeno letras de cada palabra
		sort(p1.begin(), p1.end());
		sort(p2.begin(), p2.end());
		int i = 0, j = 0;		// i recorre p1, j p2
		// recorro p1 y p2 para encontrar las letras en comun
		while ((i < (int)p1.length()) && (j < (int)p2.length())) {
			if (p1[i] == p2[j]) {
				common += p1[i];
				i++; j++;
			} else {
				if (p1[i] < p2[j])
					while ((p1[i] < p2[j]) && (i < (int)p1.length()))
						i++;
				else if (p1[i] > p2[j])
					while ((p1[i] > p2[j]) && (j < (int)p2.length()))
						j++;
			}
		}
		sort(common.begin(), common.end());
		cout << common << endl;
		getline(cin, p1);
		getline(cin, p2);
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

