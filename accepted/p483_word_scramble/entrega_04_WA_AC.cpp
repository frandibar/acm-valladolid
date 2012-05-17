
/* @JUDGE_ID:  40922FK  483  C++  */
    
/**************************************************************************
 Solution to Problem 483 - Word Scramble
 by: Francisco Dibar
 date: Dec-12-2004
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>
#include <sstream>

using namespace std;

///////////////////////////////////////////////////////////////////////////
string invertir(string str)
{
	for (int i = 0, j = str.length() - 1; i < j; i++, j--) {
		char aux = str[i];
		str[i] = str[j];
		str[j] = aux;
	}
	return str;
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

	string linea;
	getline(cin, linea);
	while (!cin.eof()) {
		istringstream stream_input(linea);
		
		string palabra;
		stream_input >> palabra;
		if (palabra != "") 
			cout << invertir(palabra);
		while (!stream_input.eof()) {		
			stream_input >> palabra;
			cout << " " << invertir(palabra);
		}
		cout << endl;
		getline(cin, linea);
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */
