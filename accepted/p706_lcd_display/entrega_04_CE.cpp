/* @JUDGE_ID:  40922FK  706  C++  */
    
/*************************************************************************
 Solution to Problem 706 - LCD Display
 by: Francisco Dibar
 date: Dec-12-2004
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 

using namespace std;

///////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	int l_seg;		// la longitud de cada segmento
	string nro;
/*		 -			 0		fila 0
		| |		1 3
		 -			 2
		| |		5 6
		 -			 4		fila 4
*/
	char mat_segmentos[10][7] = { 
							{ '-', '|', ' ', '|', '-', '|', '|'},	// 0
							{ ' ', ' ', ' ', '|', ' ', ' ', '|'},	// 1
							{ '-', ' ', '-', '|', '-', '|', ' '},	// 2
							{ '-', ' ', '-', '|', '-', ' ', '|'},	// 3 
							{ ' ', '|', '-', '|', ' ', ' ', '|'},	// 4 
							{ '-', '|', '-', ' ', '-', ' ', '|'},	// 5 
							{ '-', '|', '-', ' ', '-', '|', '|'},	// 6 
							{ '-', ' ', ' ', '|', ' ', ' ', '|'},	// 7 
							{ '-', '|', '-', '|', '-', '|', '|'},	// 8 
							{ '-', '|', '-', '|', '-', ' ', '|'}};	// 9

	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	cin >> l_seg >> nro;
	while (l_seg && (nro != "0")) {
		for (int fila = 0; fila < 5; fila++) {		// para cada fila
			if (fila % 2 == 0) {		
				// colocar los segmentos horizontales
				for (int dig = 0; dig < nro.length(); dig++) {	
					// para cada digito
					cout << " ";
					for (int l = 0; l < l_seg; l++) {
						cout << mat_segmentos[nro[dig]-'0'][fila];
					}
					// colocar un espacio entre digitos, 
					// salvo que sea el ultimo
					(dig < (nro.length()-1) ? cout << "  " : cout << " ");
				}
				cout << endl;
			} else {			// colocar los segmentos verticales
				for (int ll = 0; ll < l_seg; ll++) {
					for (int dig = 0; dig < nro.length(); dig++) {
						if (fila == 1) {
							cout << mat_segmentos[nro[dig]-'0'][1];
							for (int l = 0; l < l_seg; l++) 
								cout << " ";
							cout << mat_segmentos[nro[dig]-'0'][3];
						} else {	// fila == 3
							cout << mat_segmentos[nro[dig]-'0'][5];
							for (int l = 0; l < l_seg; l++) 
								cout << " ";
							cout << mat_segmentos[nro[dig]-'0'][6];
						}
						if (dig < (nro.length()-1)) cout << " ";
					}
					cout << endl;
				}
			}
		}
		cout << endl;
		cin >> l_seg >> nro;
	}
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

