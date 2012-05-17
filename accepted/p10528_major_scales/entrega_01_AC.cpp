/* @JUDGE_ID:  40922FK  10528  C++  */
    
/**************************************************************************
 Solution to Problem 10528 - Major Scales
 by: Francisco Dibar
 date: Dec-07-2004
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

//#define ONLINE_JUDGE 

#define FIN		"END"
#define DO		"C"
#define DOs		"C#"
#define RE		"D"
#define REs		"D#"
#define MI		"E"
#define FA		"F"
#define FAs		"F#"
#define SOL		"G"
#define SOLs	"G#"
#define LA		"A"
#define LAs		"A#"
#define SI		"B"

#define nDO		0
#define nDOs	1
#define nRE		2
#define nREs	3
#define nMI		4
#define nFA		5
#define nFAs	6
#define nSOL	7
#define nSOLs	8
#define nLA		9
#define nLAs	10
#define nSI		11

using namespace std;

///////////////////////////////////////////////////////////////////////////
inline string obtener_nota(int nro_nota)
{
	switch (nro_nota) {
		case nDO:	return DO; break;
		case nDOs:	return DOs; break;
		case nRE:	return RE; break;
		case nREs:	return REs; break;
		case nMI:	return MI; break;
		case nFA:	return FA; break;
		case nFAs:	return FAs; break;
		case nSOL:	return SOL; break;
		case nSOLs:	return SOLs; break;
		case nLA:	return LA; break;
		case nLAs:	return LAs; break;
		case nSI:	return SI; break;
	}
}

///////////////////////////////////////////////////////////////////////////
inline int obtener_nro_nota(string nota)
{
	if (nota == DO) return nDO;
	else if (nota == DOs)	return nDOs;
	else if (nota == RE)		return nRE;
	else if (nota == REs)	return nREs;
	else if (nota == MI)		return nMI;
	else if (nota == FA)		return nFA;
	else if (nota == FAs)	return nFAs;
	else if (nota == SOL)	return nSOL;
	else if (nota == SOLs)	return nSOLs;
	else if (nota == LA)		return nLA;
	else if (nota == LAs)	return nLAs;
	else if (nota == SI)		return nSI;
}

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

	int excluir[12][5] = {	{ nRE, nMI, nFAs, nLA, nSI },			// DO		C
									{ nDO, nREs, nFA, nSOL, nLAs },		// DO#	
									{ nDOs, nMI, nFAs, nSOLs, nSI },		// RE		D							
									{ nDO, nRE, nFA, nSOL, nLA },			// RE#
									{ nDOs, nREs, nFAs, nSOLs, nLAs },	// MI		E
									{ nRE, nMI, nSOL, nLA, nSI },			// FA		F
									{ nDO, nREs, nFA, nSOLs, nLAs },		// FA#
									{ nDOs, nMI, nFAs, nLA, nSI },		// SOL	G
									{ nDO, nRE, nFA, nSOL, nLAs },		// SOL#
									{ nDOs, nREs, nFAs, nSOLs, nSI },	// LA		A
									{ nDO, nRE, nMI, nSOL, nLA },			// LA#	
									{ nDOs, nREs, nFA, nSOLs, nLAs }		// SI		B
								};
	string input;
	getline(cin, input);
	while ((input != FIN) && (!cin.eof())) {
		vector<bool> vec_possible_keys(12, true);	// inicializo en true

		istringstream is_input(input);
		while (!is_input.eof()) {
			string nota;
			int nro_nota;
			is_input >> nota;

			nro_nota = obtener_nro_nota(nota);

			for (int i = 0; i < 5; i++) {
				int nota_a_excluir = excluir[nro_nota][i];
				vec_possible_keys[nota_a_excluir] = false;
			}
		}
		// mostrar la lista resultante
		bool primera_nota = false;
		for (int i = 0; i < 12; ++i) {
			if (vec_possible_keys[i]) {
				string nota = obtener_nota(i);
				if (!primera_nota) {
					cout << nota;
					primera_nota = true;
				} else
					cout << " " << nota;
			}
		}
		cout << endl;		
		getline(cin, input);
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */


