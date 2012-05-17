
/* @JUDGE_ID:  40922FK  10098  C++  */
    
/******************************************************************************
 Solution to Problem 10098 - Generating Fast, Sorted Permutation
 by: Francisco Dibar
 date: May-29-2004
******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>		// next_permutation, sort
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

	int bloques;
	cin >> bloques;
	for (int i = 0; i < bloques; i++) {
		string str;
		cin >> str;
		// ordenar str
		sort(str.begin(), str.end());
		// generar todas las permutaciones
		os_output << str << endl;
		while (next_permutation(str.begin(), str.end()))
			os_output << str << endl;
		if (i < bloques-1) os_output << endl;
	}
	cout << os_output.str();
	return 0;
}

