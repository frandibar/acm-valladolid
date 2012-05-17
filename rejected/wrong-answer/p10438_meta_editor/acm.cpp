
/* @JUDGE_ID:  40922FK  10438  C++  */
    
/******************************************************************************
 Solution to Problem 10438 - Meta Editor
 by: Francisco Dibar
 date: Jun-08-2004
******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
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

	string sz_input;
	getline(cin, sz_input);
	while (!cin.eof()) {
		istringstream is_line(sz_input);
		string word;
		set<string> set_words;
		bool put_space = false;
		while (!is_line.eof()) {
			is_line >> word;
			if (set_words.find(word) == set_words.end()) {
				// la palabra no estaba presente
				set_words.insert(word);
				if (put_space) 
					os_output << " ";
				else
					put_space = true;				
				os_output << word;
			}
		}
		getline(cin, sz_input);
		os_output << endl;
	}

	cout << os_output.str();
	return 0;
}

