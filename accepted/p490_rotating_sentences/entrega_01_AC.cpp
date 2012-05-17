
/* @JUDGE_ID:  40922FK  490  C++  */
    
/******************************************************************************
 Solution to Problem 490 - Rotating Sentences
 by: Francisco Dibar
 date: Apr-24-2004
******************************************************************************/

#include <iostream>
#include <string>

#define MAX_SENTENCES	100
#define MAX_LEN			100


using namespace std;

char mat_salida[MAX_SENTENCES][MAX_LEN];

////////////////////////////////////////////////////////////////////////////////
void init_mat_salida()
{
	for (int i = 0; i < MAX_SENTENCES; i++)
		for (int j = 0; j < MAX_LEN; j++)
			mat_salida[i][j] = ' ';
}

////////////////////////////////////////////////////////////////////////////////
void rotate_90cw(string sentence, int col)
{
	for (int i=0; i < sentence.length(); i++) 
		mat_salida[i][col] = sentence[i];
}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	init_mat_salida();

	int max_len = 0;
	string sentence = "";
	int cont_entrada = 0;		// cuenta las lineas de entrada

	getline(cin, sentence);		// leer la linea
	while ((!cin.eof()) && (cont_entrada <= MAX_SENTENCES)) {
		rotate_90cw(sentence, cont_entrada);
		cont_entrada++;
		// obtener la linea mas larga para luego no imprimir espacios en blanco
		if (sentence.length() > max_len) max_len = sentence.length();
		getline(cin, sentence);		// leer la linea
	}		
	
	// mostrar la salida
	for (int i = 0; i < max_len; i++) {
		string linea_sal(cont_entrada, ' ');
		for (int j = 0; j < cont_entrada; j++) {
			linea_sal[cont_entrada - j - 1] = mat_salida[i][j];
		}			
		cout << linea_sal << endl;			
	}
	return 0;
}

