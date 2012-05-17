/* @JUDGE_ID:  40922FK  10161  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10161 - Ant on a Chessboard
 by: Francisco Dibar
 date: Feb-15-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <cmath>

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

	int long n;
	cin >> n;
	while (n && !cin.eof()) {
		long x, y;
		long m = (long)ceil(sqrt((long double)n));
		long mxm = m*m;
		long dist = mxm - n + 1;
		
		if (m % 2 == 0) {
			// l par
			if (dist > m) {
				// paso el recodo
				x = 2*m - dist;
				y = m;
			} else {
				// antes del recodo
				x = m;
				y = dist;
			}
		} else {
			// l impar
			if (dist > m) {
				// paso el recodo
				x = m;
				y = 2*m - dist;
			} else {
				// antes del recodo
				x = dist;
				y = m;
			}
		}

		cout << x << " " << y << endl;
		cin >> n;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

