
/* @JUDGE_ID:  40922FK  483  C++  */
    
/******************************************************************************
 Solution to Problem 483 - Word Scramble
 by: Francisco Dibar
 date: Apr-25-2004
******************************************************************************/

#include <iostream>
#include <string>
#include <queue>

#include<fstream> 

//#define ONLINE_JUDGE 

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

	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

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
		if (linea == "") 
			cout << linea << endl;
		else {
			int pos_i = linea.find_first_not_of(' ');	// el primer caracter
			int pos_f = 0;
			int offset = (pos_i > 0 ? pos_i : 0);
			string salida(offset, ' ');	// inicializo con los espacios del comienzo
			// procesar cada palabra de la linea
			while (pos_i < (int)linea.length()) {
				// buscar el primer espacio en blanco desde pos_i para adelante
				pos_f = linea.find(' ', pos_i);
				if (pos_f == -1)	// si no hay espacios hasta el final
					pos_f = linea.find_last_not_of(' ') + 1;	// encontrar el ultimo caracter
				string palabra = linea.substr(pos_i, pos_f - pos_i);
				string palabra_inversa = invertir(palabra);			
				salida += palabra_inversa;
				pos_i = linea.find_first_not_of(' ', pos_f + 1);
				// agregar los espacios salteados entre palabra y palabra
				if (pos_i == -1)	// si no hay espacios hasta el final
					pos_i = linea.length();
				salida += linea.substr(pos_f, pos_i - pos_f);
			}
			cout << salida << endl;
			salida = "";
		}
	}
	return 0;
}

