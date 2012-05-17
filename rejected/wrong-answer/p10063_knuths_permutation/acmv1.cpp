
/* @JUDGE_ID:  40922FK  10063  C++  */
    
/******************************************************************************
 Solution to Problem 10063 - Knuth's Permutation
 by: Francisco Dibar
 date: May-27-2004
******************************************************************************/

#include <iostream>
#include <string>
#include <algorithm>		// next_permutation
#include <sstream>
#include <fstream>
#define ONLINE_JUDGE 

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

	string sz_input;
	cin >> sz_input;
	while (!cin.eof()) {
		while (next_permutation(sz_input.begin(), sz_input.end()))
			os_output << sz_input << endl;
		cin >> sz_input;
		if (!cin.eof()) os_output << endl;
	}

	// mostar la salida
	cout << os_output.str();
	return 0;
}

