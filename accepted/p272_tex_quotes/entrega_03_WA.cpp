
/* @JUDGE_ID:  40922FK  272  C++  */
    
/**************************************************************************
 Solution to Problem 272 - TEX Quotes
 by: Francisco Dibar
 date: May-29-2004
**************************************************************************/

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
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

	char c;
	bool start = true;
	while ((c = getchar()) != EOF) {
		if (c == '"') {
			if (start)
				cout << "``";
			else
				cout << "´´";
			start = !start;
		} else
			cout << c;
	}

	return 0;
}

