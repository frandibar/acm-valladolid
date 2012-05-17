/* @JUDGE_ID:  40922FK  441  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 441 - Lotto
 by: Francisco Dibar
 date: Mar-24-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>

#define NROS	6

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

	int k;
	cin >> k;
	while (k && !cin.eof()) {
		vector<int> vec_nros(k);
		// leer el conjunto S
		for (int j = 0; j < k; j++)
			cin >> vec_nros[j];
		
		int i0, i1, i2, i3, i4, i5;
		// hay NRO anidamientos
		for (i0 = 0; i0 < k; i0++) 
			for (i1 = i0+1; i1 < k; i1++) 
				for (i2 = i1+1; i2 < k; i2++) 
					for (i3 = i2+1; i3 < k; i3++) 
						for (i4 = i3+1; i4 < k; i4++) 
							for (i5 = i4+1; i5 < k; i5++) 
								cout << vec_nros[i0] << " " 
										<< vec_nros[i1] << " " 
										<< vec_nros[i2] << " " 
										<< vec_nros[i3] << " " 
										<< vec_nros[i4] << " " 
										<< vec_nros[i5] << endl;
		cin >> k;
		if (k && !cin.eof())
			cout << endl;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

