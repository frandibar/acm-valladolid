/* @JUDGE_ID:  40922FK  10215  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10215 - The Largest/Smallest Box...
 by: Francisco Dibar
 date: Nov-22-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <iomanip>	// precision
#include <cmath>	// sqrt

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

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

	double l, w;
	cin >> l >> w;
	while (!cin.eof()) {
		// PROCESS
		double max = ((l+w) - sqrt(l*l + w*w - l*w)) / 6.0;
		double min = 0.5 * ((w < l) ? w : l);
		
		// SHOW OUTPUT
		cout.setf(ios::fixed);
		cout.precision(3);
		cout << max << " 0.000 " << min << endl;

		// READ NEXT INPUT
		cin >> l >> w;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

