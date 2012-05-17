/* @JUDGE_ID:  40922FK  10443  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10443 - Rock, Scissors, Paper
 by: Francisco Dibar
 date: Feb-16-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>

using namespace std;

#define Rock	'R'
#define Scis	'S'
#define Paper	'P'

///////////////////////////////////////////////////////////////////////////
char amenaza(vector< vector<char> > &mat_state, int f, int c)
// devuelve el caracter que amenaza a mat_state[f][c],
// y si no tiene amenaza, devuelve mat_state[f][c].
{
	char killer;
	int filas = mat_state.size();
	int cols = mat_state[0].size();
	switch(mat_state[f][c]) {
		case Rock:  
			killer = Paper;	
			break;
		case Scis:
			killer = Rock;	
			break;
		case Paper:
			killer = Scis;	
			break;
	}
	if (((f > 0) && (mat_state[f-1][c] == killer)) || 
		((f+1 < filas) && (mat_state[f+1][c] == killer)) || 
		((c > 0) && (mat_state[f][c-1] == killer)) || 
		((c+1 < cols) && (mat_state[f][c+1] == killer)))
			return killer; 
		else
			return mat_state[f][c]; 
}

///////////////////////////////////////////////////////////////////////////
vector< vector<char> > proximo_estado(vector< vector<char> > &mat_state) 
{
	int filas = mat_state.size();
	int cols = mat_state[0].size();
	
	vector< vector<char> > mat_new_state(filas);
	mat_new_state = mat_state;

	for (int f = 0; f < filas; f++) { 
		for (int c = 0; c < cols; c++) {
			mat_new_state[f][c] = amenaza(mat_state, f, c);
		}
	}			
	return mat_new_state;
}

///////////////////////////////////////////////////////////////////////////
vector< vector<char> > obtener_estado(
										vector< vector<char> > &mat_state, int n)
// devuelve el estado luego de n transiciones
{
	vector< vector<char> > mat_new_state(mat_state.size());
	mat_new_state = mat_state;
	for (int t = 0; t < n; t++) 
		mat_new_state = proximo_estado(mat_new_state);

	return mat_new_state;
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

	int casos;

	cin >> casos;
	for (int k = 0; k < casos; k++) {
		int filas, cols, n;
		cin >> filas >> cols >> n;
		vector< vector<char> > mat_state(filas);
		// cargar el estado inicial
		for (int f = 0; f < filas; f++) {
			mat_state[f].resize(cols);
			for (int c = 0; c < cols; c++)
				cin >> mat_state[f][c];
		}
		if (filas && cols) {
			mat_state = obtener_estado(mat_state, n);
			// mostrar el estado final
			for (int f = 0; f < filas; f++) { 
				for (int c = 0; c < cols; c++)
					cout << mat_state[f][c];
				cout << endl;
			}		
		} else
			cout << endl;
		if (k < (casos-1)) cout << endl;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

