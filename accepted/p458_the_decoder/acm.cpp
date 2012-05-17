/* @JUDGE_ID:  40922FK  458  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 458 - The Decoder
 by: Francisco Dibar
 date: Feb-23-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>

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

	string line;
	getline(cin, line);
	while (!cin.eof()) {
		for (int i = 0; i < line.length(); i++)
			cout << char(line[i] - 7);
		cout << endl;
		getline(cin, line);
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

