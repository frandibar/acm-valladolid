/* @JUDGE_ID:  40922FK  10197  C++  */
    
/**************************************************************************
 Solution to Problem 10197 - Learning Portuguese
 by: Francisco Dibar
 date: Dec-29-2004
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
//	PROGRAMA PRINCIPAL
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	string portu, english;
	cin >> portu;
	getline(cin, english);	// puede tener mas de una palabra
	while (!cin.eof()) {
		string root = portu.substr(0, portu.length()-2);
		char tv = portu[portu.length()-2];		// anteultima letra
		int conjugation;
		switch (tv) {
			case 'a':	conjugation = 1; 
							break;
			case 'e':	conjugation = 2; 
							break;
			case 'i':	conjugation = 3; 
							break;
			
			default: 	conjugation = 0; 
							break;
		}
		cout << portu << " (to" << english << ")" << endl;
		if (conjugation) {
			cout << "eu        " << root << "o" << endl;
			switch (conjugation) {
				case 1:
					cout << "tu        " << root << tv << "s" << endl;
					cout << "ele/ela   " << root << tv << endl;
					cout << "nós       " << root << tv << "mos" << endl;
					cout << "vós       " << root << tv << "is" << endl;
					cout << "eles/elas " << root << tv << "m" << endl;
					break;
				case 2:
					cout << "tu        " << root << tv << "s" << endl;
					cout << "ele/ela   " << root << tv << endl;
					cout << "nós       " << root << tv << "mos" << endl;
					cout << "vós       " << root << tv << "is" << endl;
					cout << "eles/elas " << root << tv << "m" << endl;
					break;
				case 3:
					cout << "tu        " << root << "es" << endl;
					cout << "ele/ela   " << root << "e" << endl;
					cout << "nós       " << root << tv << "mos" << endl;
					cout << "vós       " << root << tv << "s" << endl;
					cout << "eles/elas " << root << "em" << endl;
					break;
			}
		} else
			cout << "Unknown conjugation" << endl;

		cin >> portu;
		getline(cin, english);	// puede tener mas de una palabra
		if (!cin.eof()) cout << endl;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

