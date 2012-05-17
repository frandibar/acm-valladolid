/* @JUDGE_ID:  40922FK  673  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 673 - Parentheses Balance
 by: Francisco Dibar
 date: Feb-23-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <stack>
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

	int k;
	cin >> k;
	string tmp;
	getline(cin, tmp);		// terminar de leer la linea
	for (int i = 0; (i < k) && !cin.eof(); i++) {
		stack<char> pila;
		string line;
		getline(cin, line);
		bool ok = true;
		for (int j = 0; (j < (int)line.length()) && ok; j++) {
			if ((line[j] == '(') || (line[j] == '['))
				pila.push(line[j]);
			else if (line[j] == ')')
				if (!pila.empty() && pila.top() == '(')
					pila.pop();
				else
					ok = false;
			else if (line[j] == ']')
				if (!pila.empty() && pila.top() == '[')
					pila.pop();
				else
					ok = false;
		}
		if (ok && pila.empty())
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

