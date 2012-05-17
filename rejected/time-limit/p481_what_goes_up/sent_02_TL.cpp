
/* @JUDGE_ID:  40922FK  481  C++  */
    
/**************************************************************************
 Solution to Problem 481 - What Goes Up
 by: Francisco Dibar
 date: Dec-12-2004
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <algorithm>		// max_element

#define SEPARADOR '-'

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

	vector<int> vec_input;
	int i;
	cin >> i;
	// leer la entrada
	while (!cin.eof()) {
		vec_input.push_back(i);
		cin >> i;
	}

	// calcular el vector de programacion dinamica
	// implementa la busqueda de secuencia maxima
	vector<int> vec_dp(vec_input.size(),1);	// inicializar con 1
	for (int i = 1; i < (int)vec_input.size(); i++) 
		for (int j = 0; j < i; j++)
			if (vec_input[j] < vec_input[i])
				if (vec_dp[i] < vec_dp[j]+1)
					vec_dp[i] = vec_dp[j]+1;

	int max_sec = *max_element(vec_dp.begin(), vec_dp.end());
	cout << max_sec << endl << SEPARADOR << endl;

	// mostrar la secuencia, se obtiene de leer vec_dp de atras para
	// adelante, e imprimiendo el elemento con max_sec y luego en 
	// orden descendente
	vector<int> vec_sec_max(max_sec);
	int prox = max_sec;
	for (int i = (int)vec_input.size()-1; (i >= 0) && (prox > 0); i--) {
		if (vec_dp[i] == prox) {
			prox--;
			vec_sec_max[prox] = vec_input[i];
		}
	}
	for (int i = 0; i < max_sec; i++) 
		cout << vec_sec_max[i] << endl;

	return 0;
}

/* @END_OF_SOURCE_CODE */
