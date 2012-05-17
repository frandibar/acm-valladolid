
/* @JUDGE_ID:  40922FK  195  C++  */
    
/**************************************************************************
 Solution to Problem 195 - Anagram
 by: Francisco Dibar
 date: Dec-11-2004
***************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>		// next_permutation
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

	int entradas;
	cin >> entradas;
	for (int i = 0; (i < entradas) && (!cin.eof()); i++) {
		string sz_input;
		cin >> sz_input;
		// A < a < B < b
		sort(sz_input.begin(), sz_input.end(), antes);
		cout << sz_input << endl;
		while (next_permutation(sz_input.begin(), sz_input.end(), antes))
//		while (next_permutation(sz_input.begin(), sz_input.end()))
			cout << sz_input << endl;
	}
	return 0;
}

