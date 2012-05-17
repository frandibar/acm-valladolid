
/* @JUDGE_ID:  40922FK  214  C++  */
    
/**************************************************************************
 Solution to Problem 214 - Code Generation
 by: Francisco Dibar
 date: Dec-19-2004
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>

using namespace std;

#define VACIO		'0'


////////////////////////////////////////////////////////////////////////////////
string reverse(const string& str)
{
	string s;
	for (int i = 0; i < (int)str.length(); i++) 
		s += str[str.length()-i-1];
	return s;
}

////////////////////////////////////////////////////////////////////////////////
string to_string(int n)
{
	int i, sign;
	string s;

	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		s += n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		s += '-';
	return reverse(s);
}

///////////////////////////////////////////////////////////////////////////
bool es_operacion(char car)
{
	return (car == '+' || 
 			car == '-' || 
 			car == '*' || 
    		car == '/' || 
      		car == '@');
}

///////////////////////////////////////////////////////////////////////////
bool operador_unario(char car)
{
	return (car == '@');
}

///////////////////////////////////////////////////////////////////////////
char letra_operacion(char car)
{
	switch(car) {
    	case '+':	return 'A'; break;
    	case '-':	return 'S'; break;
    	case '*':	return 'M'; break;
    	case '/':	return 'D'; break;
    	case '@':	return 'N'; break;
    	default:	return '?';
	}
}

///////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
///////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	string postfix;
	
	getline(cin, postfix);
	while (!cin.eof()) {
		int pila = 0;
		bool acc = false;
		char r0 = VACIO;
		for (int i = 0; i < (int)postfix.length(); i++) {
			char car = postfix[i];
			if (!es_operacion(car)) {
				if (!acc) {		// si el acc no esta cargado
					// load
					string instruccion = "L ";
					instruccion += car;
					cout << instruccion << endl;
					acc = true;
				} else if (r0 == VACIO)
					r0 = car;
				else {
					// store
					if (!operador_unario(car)) {
						string instruccion = "ST $";
						instruccion += to_string(++pila);
						cout << instruccion << endl;

						// load
						instruccion = "L ";
						instruccion += r0;
						cout << instruccion << endl;
						r0 = car;
					}
				}
			} else if (r0 != VACIO) {
				// operacion con acc
				string instruccion;
				instruccion += letra_operacion(car);
				if (!operador_unario(car)) {
					instruccion += ' ';
					instruccion += r0;
				}
				cout << instruccion << endl;

				r0 = VACIO;
			} else {
				// operacion con store
				string instruccion;
				instruccion += letra_operacion(car);
				if (!operador_unario(car)) {
					instruccion += " $";
					instruccion += to_string(pila--);
				}
				cout << instruccion << endl;
			}
		}
		getline(cin, postfix);
		if (!cin.eof()) cout << endl;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

/**************************************************************************

  PROCEDIMIENTO:

  para cada linea:
  leo caracter
  es operando?
	NO:		acc vacio?
			SI:	-->	L [caracter]
					acc != vacio

			NO:	r0 vacio?
				SI:	r0 = caracter
				NO:	---> ST $[++pila]
						 L [r0]
						 r0 = caracter

	SI:		r0 = vacio?
			NO:	---> [operacion] [r0]
					 r0 = vacio

			SI:	---> [operacion] $[pila--]

**************************************************************************/
