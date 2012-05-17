
/* @JUDGE_ID:  40922FK  10370  C++  */
    
/******************************************************************************
 Solution to Problem 10370 - Above Average
 by: Francisco Dibar
 date: June-01-2004
******************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
//#define ONLINE_JUDGE 

using namespace std;

////////////////////////////////////////////////////////////////////////////////
int contar_mayores(vector<int>& vec, double n)
{
	int cuenta = 0;
	for (int j = 0; j < vec.size(); j++)
		if (vec[j] > n) cuenta++;
	return cuenta;
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

	int casos;
	cin >> casos;

	for (int i = 0; i < casos; i++) {
		int alumnos;
		cin >> alumnos;
		vector<int> vec_notas(alumnos);
		double prom = 0;
		for (int j = 0; j < alumnos; j++) {
			cin >> vec_notas[j];
			prom += vec_notas[j];
		}
		prom /= alumnos;
		int encima = contar_mayores(vec_notas, prom);
		double porcentaje = (double)encima*100/alumnos;
		cout.setf(ios::fixed);
		cout.precision(3);
		cout << porcentaje << "%" << endl;

		//cout << setprecision(3) << fixed << porcentaje << "%" << endl;
	}

	return 0;
}

