
/* @JUDGE_ID:  40922FK  100  C++  */
    
/******************************************************************************
 Solution to Problem 100 - The 3n + 1 problem
 by: Franccinco Dibar
 date: Jan-04-2004
******************************************************************************/

#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>

#define LIMITE_INF 0
#define LIMITE_SUP 1000000

using namespace std;


/****************************************************************************/
int ciclos(int i)
{
	int cic = 1;
	int log = int(log10(i)/log10(2));
	// si es potencia de 2 no hace falta seguir calculando
	while (((pow(2,log)) != i) && (i != 1)) {	// pow(2,log) puede no ser i por el redondeo
		if ((i % 2) == 0)	// si es par
			i = i/2;
		else
			i = 3*i+1;
		log = int(log10(i)/log10(2));
		cic++;
	}
	if (i != 1)
		return cic + log;
	else
		return cic;
}

/*****************************************************************************
*	PROGRAMA PRINCIPAL
******************************************************************************/
int main(int argc, char* argv[])
{
	string linea, stri, strj;
	// recorrer el archivo de entrada
	getline(cin, linea);		// leer la linea
	while (!cin.eof()) {
		if (!linea.empty()) {
			// leer el primer nro: i
			int desde = linea.find_first_not_of(" ");	// saltear blanccout al comienzo
			linea = linea.substr(desde,linea.length()-desde);
			int hasta = linea.find_first_of(" ");
			stri = linea.substr(0,hasta);
			// leer el segundo nro: j
			linea = linea.substr(hasta,linea.length()-hasta);
			desde = linea.find_first_not_of(" ");	// saltear blanccout al comienzo
			linea = linea.substr(desde,linea.length()-desde);
			hasta = linea.find_first_of(" ");
			strj = linea.substr(0,hasta);

			int i = (int)atoi(stri.data());
			int j = (int)atoi(strj.data());
			// verificar que no se exceda el limite permitido
			if ((i <= LIMITE_INF) || (i >= LIMITE_SUP) || (j <= LIMITE_INF) || (j >= LIMITE_SUP)) {
				cerr << "Error por limite excedido (0 - 1000000)";
				return -1;
			}
			int a, b;
			if (i <= j) {
				a = i; b = j;
			} else {
				a = j; b = i;
			}
			int max = 0;
			int aux;
			while (a <= b) {
				aux = ciclos(a);
				if (aux > max) max = aux;
				a++;
			}
			char strmax[10];
			sprintf(strmax, "%d", max);
			linea = stri + " " + strj + " " + strmax;
			cout.write(linea.data(), linea.length());
		}
		cout.put('\n');
		getline(cin, linea);		// leer la linea
	}
	return 0;
}
