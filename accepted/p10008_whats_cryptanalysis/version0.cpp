
/* @JUDGE_ID:  40922FK  nnn  C++  */
    
/******************************************************************************
 Solution to Problem nnn - name
 by: Francisco Dibar
 date: May-01-2004
******************************************************************************/

#include <iostream>
#include <fstream>
#include <map>
#include <queue>			// implemento cola de prioridad
#include <sstream>
#include <cctype>		// isalpha
#include <cmath>		// log

#define ONLINE_JUDGE 

using namespace std;

class histograma {
private:
	char letra;
	int repeticion;

public:
	histograma();
	histograma(char l, int r) {
		letra = l;
		repeticion = r;
	}
	char &Letra() { return letra; }
	int &Repeticion() { return repeticion; }
	bool operator< (histograma h2) {		// aquel con menor repeticion es menor, si son iguales, menor letra
		if (repeticion <= h2.repeticion) 
			if (repeticion < h2.repeticion)
				return true;
			else
				return (letra < h2.letra);
		else
			return false;
	}
};

class rep_letra  {
public:
	static bool lt(histograma h1, histograma h2) {
		if (h1.Repeticion() <= h2.Repeticion()) 
			if (h1.Repeticion() < h2.Repeticion())
				return true;
			else
				return (h1.Letra() < h2.Letra());
		else
			return false;
	}
};

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
	cin >> lineas;
	string linea;
	getline(cin, linea);		// descartar el resto de la linea
	map<char, int> map_abc;
	int max = 0;
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
	int dig = (int)log10(max);
	dig++;

	// armo una cola de prioridad con los elementos como NNNL con N los digitos y L la letra
	// mostrar la salida en orden descendente por la cantidad, luego por la letra
	priority_queue<string> pq_abc;
	string ceros(dig, '0');

	map<char, int>::const_iterator map_chi_it;
	for (map_chi_it = map_abc.begin(); map_chi_it != map_abc.end(); map_chi_it++) {
		char *pn = new char[dig];
		itoa(map_chi_it->second, pn, 10);
		string str = ceros + pn + map_chi_it->first;
		pq_abc.push(str.substr(str.length()-dig-1, dig + 1));
//		cout << map_chi_it->first << " " << map_chi_it->second << endl;
	}

	while (!pq_abc.empty()) {
		string out = pq_abc.top();
		// a partir del string NNN..NL mostrarlo como L N..N
		int rep = atoi(out.substr(0, out.length() - 1).c_str());
		cout << out.substr(out.length() - 1, 1) << " " << rep << endl;
		pq_abc.pop();
	}

	return 0;
}

