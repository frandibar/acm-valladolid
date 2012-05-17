
/* @JUDGE_ID:  40922FK  10013  C++  */
    
/******************************************************************************
 Solution to Problem 10013 - Super long sums
 by: Francisco Dibar
 date: May-26-2004
******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

//#define ONLINE_JUDGE 

using namespace std;

////////////////////////////////////////////////////////////////////////////////
string sumar(const string& sA, const string& sB)
// devuelve la suma de dos enteros representados como string de cualquier longitud
{
	// hacer ambos strings de igual longitud colocando ceros por delante
	string s0(abs(sA.length() - sB.length()), '0');
	string s1 = sA,
			 s2 = sB;
	if (sA.length() > sB.length()) 
		s2.insert(0, s0);
	else
		s1.insert(0,s0);

	string res(s1.length()+1, '0');
	// efectuar la suma
	int carry = 0;
	for (int i = s1.length()-1; i >= 0; i--) {
		int sum = carry + s1[i] + s2[i] - 96;	// le resto el offset ascii
		carry = (sum > 9);
		res[i+1] = sum - 10*carry + 48;
	}
	res[0] = carry + 48;
	
	// quitar el 0 del comienzo
	if (res[0] == '0') 
		return res.substr(1,res.length());
	else
		return res;
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

	int bloques;
	cin >> bloques;

	queue<string> que_output;
	for (int i = 0; i < bloques; i++) {
		// leer cada bloque
		long digitos;
		cin >> digitos;
		string s1(digitos, '0');
		string s2 = s1;
		// armar los sumandos
		for (long d = 0; d < digitos; d++) 
			cin >> s1[d] >> s2[d];
		// guardar el resultado en la cola para luego imprimirlo
		que_output.push(sumar(s1, s2));
	}

	if (!que_output.empty()) {
		cout << que_output.front() << endl;
		que_output.pop();
	}
	while (!que_output.empty()) {		// puse el if anterior para evitar una linea de mas al final
		cout << endl;
		cout << que_output.front() << endl;
		que_output.pop();
	}

	return 0;
}

