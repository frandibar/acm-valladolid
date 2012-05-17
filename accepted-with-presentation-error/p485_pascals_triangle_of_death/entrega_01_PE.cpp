
/* @JUDGE_ID:  40922FK  485  C++  */
    
/******************************************************************************
 Solution to Problem 485 - Pascal's Triangle of Death
 by: Francisco Dibar
 date: Mar-09-2004
******************************************************************************/

#include <iostream>
#include <vector>
#include <string>

#define MAX		"1000000000000000000000000000000000000000000000000000000000000"	// 10^60

#define FILAS	205		// en la fila 205 alcanzo MAX

using namespace std;

// REVISAR: no tiene sentido almacenar todas las columnas siendo estas una repeticion de la primera mitad

// Para manejar nros muy grandes, los implemento como strings, y agrego funciones
// para sumar y comparar nros como string

////////////////////////////////////////////////////////////////////////////////
bool menor(const string& s1, const string& s2)
// devuelve true si s1 es menor que s2, ambos enteros representados como string
{
	// primero verificar la cantidad de digitos
	if (s1.length() < s2.length()) 
		return true;
	else if (s1.length() > s2.length())
		return false;
	else {
		// tienen igual cantidad de digitos, comparo uno a uno
		int i = 0;
		while (s1[i] == s2[i])
			i++;
		return (s1[i] < s2[i]);
	}
}

////////////////////////////////////////////////////////////////////////////////
string sumar(const string& sA, const string& sB)
// devuelve la suma de dos enteros representados como string de cualquier longitud
{
	// hacer ambos strings de igual longitud colocando ceros por delante
	string s0(abs(sA.length() - sB.length()), '0');
	string s1 = sA,
			 s2 = sB;
	if (sA.length() > sB.length()) 
		s2.insert(0, s0);
	else
		s1.insert(0,s0);

	string res(s1.length()+1, '0');
	// efectuar la suma
	int carry = 0;
	for (int i = s1.length()-1; i >= 0; i--) {
		int sum = carry + s1[i] + s2[i] - 96;	// le resto el offset ascii
		carry = (sum > 9);
		res[i+1] = sum - 10*carry + 48;
	}
	res[0] = carry + 48;
	
	// quitar el 0 del comienzo
	if (res[0] == '0') 
		return res.substr(1,res.length());
	else
		return res;
}

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	vector<string> vec_pascal(FILAS);
	
	cout << "1" << endl;
	cout << "1 1" << endl;
	// comienzo a partir de la 3ra fila
	vec_pascal[0] = "1";
	vec_pascal[1] = "1";
	bool fin = false;
	int fila = 3;
	int cols;
	(fila % 2 == 0) ? cols = fila/2 : cols = (fila+1)/2;
	while (!fin) {
		int c;
		// lo hago de cols para atras para poder usar un solo vector, si lo hago para adelante piso los valores
		for (c = cols-1; c > 0; c--) {	
			vec_pascal[c] = sumar(vec_pascal[c], vec_pascal[c-1]);		
			if (!menor(vec_pascal[c], MAX)) fin = true;	// controlar fin
		}
		// mostrar la primer mitad de columnas
		for (c = 0; c < cols; c++) {
			cout << vec_pascal[c] << " ";		
		}
		// completar el resto de las columnas de los valores obtenidos en la primera mitad
		for (c = cols; c < fila; c++) {
			vec_pascal[c] = vec_pascal[fila-c-1];		
			cout << vec_pascal[c] << " ";
		}
		if (!fin) cout << endl;		// evitar fin de linea al final
		fila++;
		(fila % 2 == 0) ? cols = fila/2 : cols = (fila+1)/2;
	}
	cout << endl;
	return 0;
}

