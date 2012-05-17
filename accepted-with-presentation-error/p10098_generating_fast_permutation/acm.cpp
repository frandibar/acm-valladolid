
/* @JUDGE_ID:  40922FK  10098  C++  */
    
/******************************************************************************
 Solution to Problem 10098 - Generating Fast, Sorted Permutation
 by: Francisco Dibar
 date: Dec-11-2004
******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>		// next_permutation, sort
//#define ONLINE_JUDGE 

using namespace std;

///////////////////////////////////////////////////////////////////////////
bool antes(char c1, char c2)
// devuelve true si c1 va antes que c2
{
	if (c1 <= 'Z' && c2 >= 'a') 
		return ((c1 + ('a' - 'A')) <= c2);
	else if (c2 <= 'Z' && c1 >= 'a') 
		return ((c2 + ('a' - 'A')) > c1);
	else
		return (c1 < c2);
}

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

	int bloques;
	cin >> bloques;
	for (int i = 0; i < bloques; i++) {
		string str;
		cin >> str;
		// ordenar str
		sort(str.begin(), str.end(), antes);
		// generar todas las permutaciones
		cout << str << endl;
		while (next_permutation(str.begin(), str.end(), antes))
			cout << str << endl;
		if (i < bloques-1) cout << endl;
	}
	return 0;
}

