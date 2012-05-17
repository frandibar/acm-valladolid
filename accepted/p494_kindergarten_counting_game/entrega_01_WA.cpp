
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

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	queue<string> que_input;
	string input;

	getline(cin, input);
	while (!cin.eof()) {
		que_input.push(input);
		getline(cin, input);
	}
	while (!que_input.empty()) {
		input = que_input.front();
		istringstream linea(input);
		que_input.pop();
		int palabras = 0;
		// procesar cada palabra de la linea
		while (!linea.eof()) {
			string word;
			
			linea >> word;
			int i = 0;
			while ((!isalpha(word[i])) && (i < (int)word.length())) 
				i++;
			if (i < (int)word.length())
				palabras++;
		}
		cout << palabras << endl;
	}
		
	return 0;
}

