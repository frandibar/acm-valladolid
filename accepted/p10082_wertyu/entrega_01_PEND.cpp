/* @JUDGE_ID:  40922FK  10082  C++  */
    
/**************************************************************************
 Solution to Problem 10082 - WERTYU
 by: Francisco Dibar
 date: Jan-13-2005
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

char vec_teclado[] = {	
	'`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',								
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\\',								
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'',								
	'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/',								
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',								
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',								
	'z', 'x', 'c', 'v', 'b', 'n', 'm' };

char tecla_izq(char tecla)
// devuelve la tecla a la izquierda de tecla
{
	// buscar la posicion de la tecla en vec_teclado
	int i;
	for (i = 0; (i < 78) && (vec_teclado[i] != tecla); i++)
		;
	// los casos especiales [ ; y , develven una letra 
	// pero no especifica si debe ser mayuscula o minuscula
	return vec_teclado[i-1];
}


int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	string linea;
	getline(cin, linea);
	while (!cin.eof()) {
		for (int i = 0; i < linea.length(); i++) {			
			if (linea[i] != ' ')
				cout << tecla_izq(linea[i]);
			else
				cout << ' ';
		}
		cout << endl;
		getline(cin, linea);
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

