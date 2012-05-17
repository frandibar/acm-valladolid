
/* @JUDGE_ID:  40922FK  483  C++  */
    
/******************************************************************************
 Solution to Problem 483 - Word Scramble
 by: Francisco Dibar
 date: Apr-25-2004
******************************************************************************/

#include <iostream>
#include <string>
#include <queue>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
string invertir(string str)
{
	for (int i = 0, j = str.length() - 1; i < j; i++, j--) {
		char aux = str[i];
		str[i] = str[j];
		str[j] = aux;
	}
	return str;
}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	queue<string> que_input;
	string linea;

	while (!cin.eof()) {
		getline(cin, linea);
		que_input.push(linea);
	}

	while (!que_input.empty()) {
		linea = que_input.front();
		que_input.pop();

		int pos_i = 0, 
			pos_f = 0;
		while (pos_i < linea.length()) {
			pos_f = linea.substr(pos_i, linea.length()).find(' ');
			if (pos_f == -1)
				pos_f = linea.length() - pos_i - 1;
			string palabra = linea.substr(pos_i, pos_f);
			pos_i += pos_f + 1;
			string inversa = invertir(palabra);
			cout << inversa << " ";
		}
		cout << endl;
	}

	return 0;
}

