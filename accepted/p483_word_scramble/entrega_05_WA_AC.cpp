
/* @JUDGE_ID:  40922FK  483  C++  */
    
/**************************************************************************
 Solution to Problem 483 - Word Scramble
 by: Francisco Dibar
 date: Feb-07-2004
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////
string reverse(const string s)
{
	string srev(s);
	for (int i = 0; i < (int)s.length(); i++)
		srev[i] = s[s.length()-1-i];
	return srev;
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
		string palabra;
		int i = 0, j = 0;
		while (j < (int)linea.length()) {
			i = linea.find_first_not_of(' ', j);
			if (i != -1) {
				j = linea.find_first_of(" \n", i+1);
				if (j == -1) j = linea.length();
				// entre i y j hay una palabra, la invierto y reemplazo
				if ((i < j) && (i >= 0)) {
					palabra = linea.substr(i, j-i);
					linea.replace(i, j-i, reverse(palabra));
				}
			} else {
				// no hay espacios en la linea, invertirla				
				palabra = linea.substr(j, linea.length()-j);
				linea.replace(j, linea.length()-j, reverse(palabra));
				j = linea.length();
			}
		}
		cout << linea << endl;
		getline(cin, linea);
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */
