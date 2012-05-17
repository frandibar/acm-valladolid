
/* @JUDGE_ID:  40922FK  482  C++  */
    
/**************************************************************************
 Solution to Problem 482 - Permutation Arrays
 by: Francisco Dibar
 date: Dec-12-2004
**************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
//#define ONLINE_JUDGE 

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

	int casos;
	string str;	// se usa para terminar de leer una linea
	cin >> casos;
	getline(cin, str);	// saltear hasta la proxima linea
	for (int i = 0; i < casos; i++) {
		int ind;
		vector<int> vec_ind;
		// leer hasta encontrar fin de linea
		while ((cin.peek() != '\n') && !cin.eof()) {		
			cin >> ind;
			vec_ind.push_back(ind);
		}
		
		// supongo igual cantidad de indices como float
		// los float los leo como strings 
		// (para evitar problemas de precision al mostrar)
		vector<string> vec_fl(vec_ind.size());
		for (int j = 0; j < (int)vec_ind.size(); j++) 
			cin >> vec_fl[j];
		
		getline(cin,str);		// saltear salto de linea

		// mostrar la salida
		for (int j = 0; j < (int)vec_ind.size(); j++) 
			cout << vec_fl[vec_ind[j]-1] << endl;

		if (i < casos-1) cout << endl;
	}
   
	return 0;
}

