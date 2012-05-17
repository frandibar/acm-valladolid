/* @JUDGE_ID:  40922FK  10137  C++  */
    
/**************************************************************************
 Solution to Problem 10137 - The Trip
 by: Francisco Dibar
 date: Jul-14-2005
**************************************************************************/
/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>	// setprecision
#include <cmath>		// modf

//#define ONLINE_JUDGE 

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

	int students;
	cin >> students;
	// mostrar dos decimales
	cout << setiosflags(ios::fixed) << setprecision(2); 
	while (students) {
		/*
		1 calculo el promedio
		2 sumo aquellos que estan por encima del promedio redondeado
		2 sumo aquellos que estan por debajo del promedio redondeado
		4 devuelvo el menor entre ambos
		*/
		vector<double> vec_amount(students);
		double	sum = 0, 
					avg = 0,
					over = 0,
					under = 0,
					exchange = 0;
		
		// calculo el promedio
		for (int i = 0; i < students; i++) {
			cin >> vec_amount[i];
			sum += vec_amount[i];
		}
		avg = 100 * sum / (double) students;
		// redondear el promedio
		double pentera;
		if (modf(avg, &pentera) < 0.5)
			avg = pentera / (double) 100;
		else
			avg = (pentera + 1) / (double) 100;
		// sumar los que estan por encima y por debajo del promedio
		for (int j = 0; j < students; j++) {
			if (vec_amount[j] < avg)
				under += avg - vec_amount[j];
			else if (vec_amount[j] > avg)
				over += vec_amount[j] - avg;
		}		
		// devolver el menor entre ambos
		exchange = (over < under ? over : under);
		cout << "$" << exchange << endl;
		cin >> students;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

