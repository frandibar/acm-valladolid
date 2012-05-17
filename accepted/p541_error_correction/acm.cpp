
/* @JUDGE_ID:  40922FK  541  C++  */
    
/******************************************************************************
 Solution to Problem 541 - Error Correction
 by: Francisco Dibar
 date: May-30-2004
******************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
//#define ONLINE_JUDGE 

using namespace std;

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

	ostringstream os_output;

	// opciones posibles para que la matriz sea par cambiando 1 solo bit: 
	// 1 fila impar y 1 columna impar
	int cols;
	cin >> cols;

	while (cols) {
		int fila_impar = -1,
			col_impar = -1;
		vector< vector<int> > mat_bits(cols, vector<int>(cols));	// matriz de cols x cols
		
		// cargar la matriz y controlar paridad de filas
		bool corrupt = false;
		for (int f = 0; f < cols; f++) {
			int par_f = 0;
			for (int c = 0; c < cols; c++) {
				cin >> mat_bits[f][c];
				if (mat_bits[f][c]) par_f++;
			}
			if (par_f % 2 != 0)					// si la paridad de la fila es impar
				if (fila_impar != -1)
					corrupt = true;	// continuo leyendo para terminar de cargar la matriz
				else
					fila_impar = f;
		}
		
		// recorrer nuevamente la matriz y controlar paridad de columnas
		for (int c = 0; c < cols && !corrupt; c++) {
			int par_c = 0;
			for (int f = 0; f < cols; f++) {
				if (mat_bits[f][c]) par_c++;
			}
			if (par_c % 2 != 0)					// si la paridad de la col es impar
				if (col_impar != -1)
					corrupt = true;
				else
					col_impar = c;
		}
		
		// mostrar la salida
		if (corrupt)
			os_output << "Corrupt" << endl;
		else if ((fila_impar != -1) && (col_impar != -1))
			// sumo 1 a fila_impar y col_impar porque los indices deben empezar en 1 y no en 0
			os_output << "Change bit (" << fila_impar+1 << "," << col_impar+1 << ")" << endl;
		else if ((fila_impar == -1) && (col_impar == -1))
			os_output << "OK" << endl;
		
		cin >> cols;
	}
	
	cout << os_output.str();
	return 0;
}

