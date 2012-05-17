
/* @JUDGE_ID:  40922FK  195  C++  */
    
/******************************************************************************
 Solution to Problem 195 - Anagram
 by: Francisco Dibar
 date: Jun-04-2004
******************************************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>		// next_permutation
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

	int entradas;
	cin >> entradas;
	for (int i = 0; (i < entradas) && (!cin.eof()); i++) {
		string sz_input;
		cin >> sz_input;
		sort(sz_input.begin(), sz_input.end());
		os_output << sz_input << endl;
		while (next_permutation(sz_input.begin(), sz_input.end()))
			os_output << sz_input << endl;
	}
	// mostar la salida
	cout << os_output.str();
	return 0;
}

