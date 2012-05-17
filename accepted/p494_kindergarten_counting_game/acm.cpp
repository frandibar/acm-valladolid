
/* @JUDGE_ID:  40922FK  494  C++  */
    
/******************************************************************************
 Solution to Problem 494 - Kindergarten Counting Game
 by: Francisco Dibar
 date: May-13-2004
******************************************************************************/

#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <cctype>		// isalpha
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

	queue<string> que_input;
	string input;

	getline(cin, input);
	while (!cin.eof()) {
		que_input.push(input);
		getline(cin, input);
	}
	while (!que_input.empty()) {
		input = que_input.front();
		que_input.pop();
		int palabras = 0;
		bool en_palabra = false;
		// procesar cada palabra de la linea
		for (int i = 0; i < input.length(); i++) {
			// saltear los caracteres que no son letras
			if (isalpha(input[i]) && !en_palabra) {	
				// comienza una palabra
				palabras++;
				en_palabra = true;
			} else if (!isalpha(input[i]) && en_palabra) 				
				en_palabra = false;	// termina una palabra
		}
		cout << palabras << endl;
	}
		
	return 0;
}

