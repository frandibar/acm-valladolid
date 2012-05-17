
/* @JUDGE_ID:  40922FK  482  C++  */
    
/**************************************************************************
 Solution to Problem 482 - Permutation Arrays
 by: Francisco Dibar
 date: Feb-07-2004
**************************************************************************/

#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <string>
#include <sstream>
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
	// se asume que hay una linea en blanco entre cada caso
	int casos;
	cin >> casos;
	string linea;
	getline(cin, linea);	// saltear hasta la proxima linea
	getline(cin, linea);
	if (linea.empty()) getline(cin, linea);	
	for (int i = 0; i < casos; i++) {
		istringstream is_indices(linea);
		vector<int> vec_ind;
		while (!is_indices.eof()) {
			int ind;
			is_indices >> ind;
			if (!is_indices.fail())
				vec_ind.push_back(ind);
		}
		
		// supongo igual cantidad de indices como float
		// los float los leo como strings 
		// (para evitar problemas de precision al mostrar)
		vector<string> vec_fl(vec_ind.size());
		getline(cin, linea);		// ignorar resto de la linea
		istringstream is_floats(linea);
		for (int j = 0; j < (int)vec_ind.size(); j++) {
			string fl;
			is_floats >> fl;
			if (!is_floats.fail())
				vec_fl[j] = fl;
		}
		
		getline(cin, linea);		// ignorar resto de la linea
		getline(cin, linea);		// saltear linea en blanco
		if (linea.empty()) getline(cin, linea);	

		// mostrar la salida
		for (int j = 0; j < (int)vec_ind.size(); j++) 
			cout << vec_fl[vec_ind[j]-1] << endl;

		if (i < casos-1) cout << endl;
	}
   
	return 0;
}

