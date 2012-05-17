
/* @JUDGE_ID:  40922FK  307  C++  */
    
/******************************************************************************
 Solution to Problem 307 - Sticks
 by: Francisco Dibar
 date: May-25-2004
******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>			// sort
#include <functional>      // greater<int>()

#include <fstream>
//#define ONLINE_JUDGE 

using namespace std;

////////////////////////////////////////////////////////////////////////////////
bool hay_grupos_de_L(vector<int>& vec_int, int suma, int cant_grupos)
// devuelve true si hay cant_grupos grupos disjuntos que suman suma
// vec_int es un vector ordenado de forma descendente
{
//	vector<bool> vec_esta(vec_int.size());		// indica si el elemento de vec_int ya fue considerado
	vector<int> vec_grupos(cant_grupos);

	// barro vec_int, y voy guardando la suma en vec_grupos[g].
	// si la suma excede suma, lo guardo en vec_grupos[g+1] y asi...	
	int g = 0;
	for (int i = 0; i < vec_int.size(); i++) {
		while ((vec_grupos[g] + vec_int[i] > suma) && (g <= cant_grupos))
			g++;
		if (g <= cant_grupos)
			vec_grupos[g] += vec_int[i];
		else
			return false;
		g = 0;
	}
	// controlar que todos los grupos suman suma
	for (int j = 0; j < cant_grupos; j++)
		if (vec_grupos[j] != suma) return false;
	
	return true;
}

////////////////////////////////////////////////////////////////////////////////
int longitud_minima(vector<int>& vec_sticks, int suma, int lmin) 
// devuelve la longitud minima que pueden tener los sticks
{
	// busco los ki entero tal que suma/ki es entero y >= lmin.	k:[1..suma/lmin]
	// suma/ki >= lmin  ->  ki <= suma/lmin  	
	// ki es la cantidad de palos iguales que suman suma.
	// o sea que suma/ki es la longitud de cada uno de ellos
	int n = suma/lmin;	
	vector<int> vec_k(n);
	int nki = 0;	// m guarda la cantidad de ki obtenidos
	for (int ki = n; ki > 0; ki--) {
		if (suma % ki == 0)
			vec_k[nki++] = ki;	// asigna, luego incrementa m
	}

	// busco para cada ki (me detengo con el primero que encuentro solucion)
	// si existe un L = suma/ki, de modo que hayan ki grupos de palitos que suman L
	// los grupos no necesariamente deben tener la misma cantidad de palitos
	
	// ordeno los palitos en orden descendente
	sort(vec_sticks.begin(), vec_sticks.end(), greater<int>());
	for (int i = 0; i < nki; i++) {
		int L = suma/vec_k[i];
		if (hay_grupos_de_L(vec_sticks, L, vec_k[i]))
			return L;
	}
	return 0;
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

	queue<int> que_output;
	int sticks;
	cin >> sticks;
	while (sticks > 0) {
		int suma = 0,
			 max = 0;
		vector<int> vec_sticks(sticks);
		// leer la longitud de los sticks
		for (int i = 0; i < sticks; i++) {
			cin >> vec_sticks[i];
			suma += vec_sticks[i];
			if (vec_sticks[i] > max) max = vec_sticks[i];
		}
		// calcular la longitud minima
		que_output.push(longitud_minima(vec_sticks, suma, max));
		cin >> sticks;
	}

	// mostrar la salida
	while (!que_output.empty()) {
		cout << que_output.front() << endl;
		que_output.pop();
	}

	return 0;
}

