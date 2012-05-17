/* @JUDGE_ID:  40922FK  10137  C++  */
    
/******************************************************************************
 Solution to Problem 10137 - The Trip
 by: Francisco Dibar
 date: Aug-15-2004
******************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>	// setprecision

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
	int students;
	cin >> students;
	// mostrar dos decimales
	os_output << setiosflags(ios::fixed) << setprecision(2); 
	while (students) {
		/*
		1 sumo todos los valores
		2 calculo el promedio
		3 al promedio le resto 0,005
		4 para aquellos valores menores que el promedio minimo, sumo la resta de este promedio por ellos
		*/
		vector<double> vec_amount(students);
		double sum = 0, avg = 0, exchange = 0;
		for (int i = 0; i < students; i++) {
			cin >> vec_amount[i];
			sum += vec_amount[i];
		}
		avg = sum / (double)students - 0.005;
		for (int j = 0; j < students; j++) {
			if (vec_amount[j] < avg)
				exchange += avg - vec_amount[j];
		}
		os_output << "$" << exchange << endl;
		cin >> students;
	}
	cout << os_output.str();
	return 0;
}

/* @END_OF_SOURCE_CODE */

