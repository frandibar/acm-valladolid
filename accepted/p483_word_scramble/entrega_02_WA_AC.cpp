
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

	// leer cada linea de entrada y meterla en la cola que_input
	getline(cin, linea);
	while (!cin.eof()) {
		que_input.push(linea);
		getline(cin, linea);
	}

	while (!que_input.empty()) {
		linea = que_input.front();
		que_input.pop();

		int pos_i = linea.find_first_not_of(' ');	// el primer caracter
		int pos_f = 0;
		string salida = "";
		// procesar cada palabra de la linea
		while (pos_i < linea.length()) {
			// buscar el primer espacio en blanco desde pos_i para atras
			pos_f = linea.find(' ', pos_i);
			if (pos_f == -1)
				pos_f = linea.find_last_not_of(' ') + 1;	// encontrar el ultimo caracter
			string palabra = linea.substr(pos_i, pos_f - pos_i);
			pos_i = linea.find_first_not_of(' ', pos_f + 1);
			string inversa = invertir(palabra);
			salida += inversa + " ";
		}
		// quitar el espacio al final y mostrar la linea al reves
		if (salida != "") {	// evita una linea en blanco al final
			cout << salida.substr(0, salida.length()-1);
			salida = "";
		}
		cout << endl;
	}
	return 0;
}

