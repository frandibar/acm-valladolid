/* @JUDGE_ID:  40922FK  10038  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10038 - Jolly Jumpers
 by: Francisco Dibar
 date: Feb-18-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>

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

	// un jolly jumper canonico puede ser
	// n 1 n-1 2 n-2 3 n-3 4 n-4 5 ...
	// cuya secuencia da
	// n-1 n-2 n-3 ... 1
	int n;
	cin >> n;
	while (!cin.eof()) {
		vector<bool> vec(n+1);
		int s, t, p;
		bool jolly;
		cin >> s;
		// cargar el vector en true para cada resultado
		for (int i = 1; (i < n) && !cin.eof(); i++) {
			cin >> t;
			p = abs(s-t);
			if (p < n)
				vec[p] = true;
			s = t;
		}
		// verificar si vec[i] = true para todo i
		int j; 
		for (j = 1; j <= n && vec[j]; j++)
			;
		jolly = (j == n);
		
		// mostrar la salida
		if (jolly || (n == 1)) 
			cout << "Jolly" << endl;
		else  
			cout << "Not jolly" << endl;
		
		cin >> n;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

