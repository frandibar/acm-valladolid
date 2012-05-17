
/* @JUDGE_ID:  40922FK  10008  C++  */
    
/******************************************************************************
 Solution to Problem 10008 - What's Cryptanalysis?
 by: Francisco Dibar
 date: May-01-2004
******************************************************************************/

#include <iostream>
#include <fstream>
#include <map>
#include <queue>			// implemento cola de prioridad
#include <cctype>		// isalpha
#include <cmath>		// log
#include <string>

//#define ONLINE_JUDGE

using namespace std;

////////////////////////////////////////////////////////////////////////////////
void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

////////////////////////////////////////////////////////////////////////////////
void itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10 ) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
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

	int lineas;
	string linea;
	map<char, int> map_abc;
	int max = 0;

	cin >> lineas;
	getline(cin, linea);		// descartar el resto de la linea
	// leer y procesar cada linea
	for (int i = 0; i < lineas; i++) {
		getline(cin, linea);
		// procesar cada letra
		for (int j = 0; j < (int)linea.length(); j++) {
			if (isalpha(linea[j])) {
				map_abc[toupper(linea[j])]++;
				if (map_abc[toupper(linea[j])] > max)
					max = map_abc[toupper(linea[j])];
			}
		}
	}
	int dig = (int)log10(max) + 1;

	// armo una cola de prioridad con los elementos como NNNL con N los digitos y L la letra
	// mostrar la salida en orden descendente por la cantidad, luego por la letra
	priority_queue<string> pq_abc;
	string ceros(dig, '0');

	map<char, int>::const_iterator map_chi_it;
	for (map_chi_it = map_abc.begin(); map_chi_it != map_abc.end(); map_chi_it++) {
		char *pn = new char[dig];
		itoa(map_chi_it->second, pn);
		// meter en la cola cada letra con su repeticion, para luego obtener un orden por rep
		// para obtener un orden ascendente de letra, guardo el complemento de la misma
		char l = 'Z' - map_chi_it->first;
		string str = ceros + pn + l;
		pq_abc.push(str.substr(str.length()-dig-1, dig + 1));
	}

	// mostrar los elementos de la cola
	while (!pq_abc.empty()) {
		string out = pq_abc.top();
		// a partir del string NNN..NL mostrarlo como L N..N
		int rep = atoi(out.substr(0, out.length() - 1).c_str());
		// obtener la letra original
		char l = 'Z' - out.substr(out.length() - 1, 1).c_str()[0]; 
		cout << l << " " << rep << endl;
		pq_abc.pop();
	}

	return 0;
}

