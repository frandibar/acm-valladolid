
/* @JUDGE_ID:  40922FK  10062  C++  */
    
/******************************************************************************
 Solution to Problem 10062 - Tell me the frequencies!
 by: Francisco Dibar
 date: May-27-2004
******************************************************************************/

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <sstream>
#include <fstream>

//#define ONLINE_JUDGE 

using namespace std;

////////////////////////////////////////////////////////////////////////////////
struct histograma {
	int letra,
		 frecuencia;
};

////////////////////////////////////////////////////////////////////////////////
bool sort_frec_asc(const histograma& h1, const histograma& h2)
// funcion binaria para ordenar la lista por orden ascendente de frecuencia y descendente de letra
{
	if (h1.frecuencia > h2.frecuencia)
		return false;
	else if (h1.frecuencia == h2.frecuencia)
		return (h1.letra > h2.letra);
	return true;
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

	ostringstream os_output;	// stream para la salida
	
	string linea;
	getline(cin, linea);
	// leer y procesar cada linea
	while (!cin.eof()) {
		map<int, int> map_abc;
		// procesar cada letra
		for (int j = 0; j < (int)linea.length(); j++) {
			if ((linea[j] >= 32) && (linea[j] < 128)) {
				map_abc[linea[j]]++;
			}
		}

		list<histograma> lst_abc;
		// cargar la lista con los elementos del mapa
		map<int, int>::const_iterator map_chi_it;
		for (map_chi_it = map_abc.begin(); map_chi_it != map_abc.end(); map_chi_it++) {
			histograma hist;
			hist.letra = map_chi_it->first;
			hist.frecuencia = map_chi_it->second;
			lst_abc.push_back(hist);
		}

		lst_abc.sort(sort_frec_asc);
		// mostrar los elementos de la lista
		while (!lst_abc.empty()) {
			histograma hist = lst_abc.front();
			lst_abc.pop_front();
			os_output << hist.letra << " " << hist.frecuencia << endl;
		}
		os_output << endl;
		getline(cin, linea);
	}
	
	// mostrar la salida
	cout << os_output.str();
	return 0;
}

