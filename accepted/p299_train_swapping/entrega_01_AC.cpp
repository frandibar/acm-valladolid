/* @JUDGE_ID:  40922FK  299  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 299 - Train Swapping
 by: Francisco Dibar
 date: Mar-28-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>

using namespace std;

///////////////////////////////////////////////////////////////////////////
int steps(vector<int>& vec)
// devuelve la cantidad de swaps contiguos necesarios para ordenar vec
{
	int swaps = 0;
	bool ordenado = false;
	while (!ordenado) {
		ordenado = true;
		for (int i = 0; i < (int)vec.size()-1; i++) {
			if (vec[i] > vec[i+1]) {
				ordenado = false;
				int aux = vec[i];
				vec[i] = vec[i+1];
				vec[i+1] = aux;
				swaps++;
			}
		}
	}
	return swaps;
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

	int casos;
	cin >> casos;
	// para cada caso
	for (int k = 0; k < casos; k++) {
		int vagones;
		cin >> vagones;
		vector<int> vec(vagones);
		// leer los vagones
		for (int i = 0; i < vagones; i++)
			cin >> vec[i];
		// ordenar el tren
		int swaps = steps(vec);
		cout << "Optimal train swapping takes " << swaps <<  " swaps." << endl;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

