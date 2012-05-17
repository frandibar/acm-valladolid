/* @JUDGE_ID:  40922FK  102  C++  */
    
/**************************************************************************
 Solution to Problem 102 - Ecological Bin Packing
 by: Francisco Dibar
 date: Mar-21-2005
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>

#define B		0
#define G		1
#define C		2
#define BIN1	0
#define BIN2	3
#define BIN3	6

//#define BINS	3
//#define COLORS	3
#define BxC		9	// BINS x COLORS

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

	// solucion por el metodo de la fuerza bruta
	// para n grandes, se deberia resolver por dp
	int vec[BxC];	
	cin >> vec[0];
	while (!cin.eof()) {
		string orden = "BCG";
		long min = 0;

		// cargar el vector con la entrada
		for (int i = 1; i < BxC; i++) {
			cin >> vec[i];
			min += vec[i];
		}
		// min toma el maximo valor (cota superior)
		long suma;
		// BCG
		suma =	vec[BIN2 + B] + vec[BIN3 + B] +
					vec[BIN1 + C] + vec[BIN3 + C] +
					vec[BIN1 + G] + vec[BIN2 + G];
		if (suma < min) {
			min = suma;
			orden = "BCG";
		}
		// BGC
		suma =	vec[BIN2 + B] + vec[BIN3 + B] +
					vec[BIN1 + G] + vec[BIN3 + G] +
					vec[BIN1 + C] + vec[BIN2 + C];
		if (suma < min) {
			min = suma;
			orden = "BGC";
		}
		// CBG
		suma =	vec[BIN2 + C] + vec[BIN3 + C] +
					vec[BIN1 + B] + vec[BIN3 + B] +
					vec[BIN1 + G] + vec[BIN2 + G];
		if (suma < min) {
			min = suma;
			orden = "CBG";
		}
		// CGB
		suma =	vec[BIN2 + C] + vec[BIN3 + C] +
					vec[BIN1 + G] + vec[BIN3 + G] +
					vec[BIN1 + B] + vec[BIN2 + B];
		if (suma < min) {
			min = suma;
			orden = "CGB";
		}
		// GBC
		suma =	vec[BIN2 + G] + vec[BIN3 + G] +
					vec[BIN1 + B] + vec[BIN3 + B] +
					vec[BIN1 + C] + vec[BIN2 + C];
		if (suma < min) {
			min = suma;
			orden = "GBC";
		}
		// GCB
		suma =	vec[BIN2 + G] + vec[BIN3 + G] +
					vec[BIN1 + C] + vec[BIN3 + C] +
					vec[BIN1 + B] + vec[BIN2 + B];
		if (suma < min) {
			min = suma;
			orden = "GCB";
		}
		cout << orden << " " << min << endl;
		cin >> vec[0];
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

