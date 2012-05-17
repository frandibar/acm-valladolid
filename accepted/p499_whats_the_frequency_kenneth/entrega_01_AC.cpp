
/* @JUDGE_ID:  40922FK  499  C++  */
    
/******************************************************************************
 Solution to Problem 499 - What's The Frequency, Kenneth?
 by: Francisco Dibar
 date: May-25-2004
******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>		// sort
#include <map>
#include <cctype>		// isalpha
#include <string>

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

	string linea;
	ostringstream os_output;

	getline(cin, linea);
	while (!cin.eof()) {
		// procesar cada linea
		map<char, int> map_abc;
		int max = 0;
		string sz_max = "";
		for (int j = 0; j < (int)linea.length(); j++) {
			if (isalpha(linea[j])) {
				map_abc[(linea[j])]++;
				if (map_abc[(linea[j])] > max) {
					max = map_abc[(linea[j])];
					sz_max = linea[j];
				} else if (map_abc[(linea[j])] == max) {
					// agrego la letra a la lista de max
					sz_max += linea[j];
				}
			}
		}
		sort(sz_max.begin(), sz_max.end());
		os_output << sz_max << " " << max << endl;
		getline(cin, linea);
	}
	
	cout << os_output.str();
	return 0;
}

