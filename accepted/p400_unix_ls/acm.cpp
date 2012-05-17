
/* @JUDGE_ID:  40922FK  400  C++  */
/* @BEGIN_OF_SOURCE_CODE */        
/**************************************************************************
 Solution to Problem 400 - Unix ls
 by: Francisco Dibar
 date: Aug-12-2005
**************************************************************************/
//#define DEBUG 
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <string>
#include <algorithm>	// sort
#include <cmath>		// ceil

using namespace std;

#define SEPARADOR		"------------------------------------------------------------"
#define LINEA_VACIA	"                                                            "
#define MAX_LEN					60
#define ESPACIO_ENTRE_COLS		2
#define SEPARADOR_COLS			"  "	// ESPACIO_ENTRE_COLS blancos


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

	int files;
	cin >> files;
	while (!cin.eof()) {

		// READ INPUT
		vector<string> v_nombres(files);		
		int max_len = 0;
		for (int i = 0; i < files; i++) {
			cin >> v_nombres[i];
			// guardar la maxima longitud
			if ((int)v_nombres[i].length() > max_len) 
				max_len = v_nombres[i].length();
		}
		
		// PROCESS
		sort(v_nombres.begin(), v_nombres.end());
		cout << SEPARADOR << endl;
		// max.cols + 2(cols-1) <= 60
		// cols <= 62 / (max + 2)
		// lineas = size / cols
		int cols = (int) floor((double)(MAX_LEN + ESPACIO_ENTRE_COLS) / (double)(max_len + 2));
//		div_t lin = div(files, cols);
//		int lineas = lin.quot;
//		if (lin.rem > 0) lineas++;
		int lineas = (int) ceil((double) files / cols);
		for (int i = 0; i < lineas; i++) {
			string linea = "";
			string linea_vacia = LINEA_VACIA;
			int j;
			for (j = 0; (j < cols-1) && (j < files); j++) {
				string archivo = v_nombres[j*lineas + i];
				archivo += linea_vacia.substr(0, max_len - archivo.length()) + SEPARADOR_COLS;
				linea += archivo;
			}
			if (j < files) {
				if ((cols-1)*lineas + i < files) {
					string archivo = v_nombres[(cols-1)*lineas + i];
					archivo += linea_vacia.substr(0, max_len - archivo.length());
					linea += archivo;
				}
			}
			// SHOW OUTPUT
			cout << linea << endl;
		}
		cin >> files;
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

