
/* @JUDGE_ID:  40922FK  272  C++  */
    
/******************************************************************************
 Solution to Problem 272 - TEX Quotes
 by: Francisco Dibar
 date: May-29-2004
******************************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
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

	string linea;
	getline(cin, linea);
	bool start = true;
	while (!cin.eof()) {
		int pos = linea.find("\"");
		while (pos != string::npos) {
			if (start) {
				// buscar reemplazar por ``
				linea.replace(pos, 1, "`");
				linea.insert(pos, "`");
			} else {
				// buscar reemplazar por ´´
				linea.replace(pos, 1, "´");
				linea.insert(pos, "´");
			}
			start = !start;
			pos = linea.find("\"");
		}
		os_output << linea << endl;
		getline(cin, linea);
	}

	cout << os_output.str();
	return 0;
}

