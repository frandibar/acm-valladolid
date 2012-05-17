/* @JUDGE_ID:  40922FK  579  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 579 - ClockHands
 by: Francisco Dibar
 date: Mar-23-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 

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

	int hh, mm;
	char sep;
	cin >> hh >> sep >> mm;
	while (!(hh == 0 && sep == ':' && mm == 0) && !cin.eof()) {
		/*	
			60'__ 30º			60'__ 360º	
			 1'__ x = 0.5º		 1'__ x = 6º
		*/
		double shorthand = 30 * (double)hh + 0.5 * (double)mm;
		double longhand = 6 * (double)mm;
		// angulo = abs(shorthand - longhand)
		double angulo = (shorthand > longhand ? shorthand - longhand : longhand - shorthand);
		if (angulo > 180) 
			angulo = 360 - angulo;
		cout.setf(ios::fixed);
		cout.precision(3);
		cout << angulo << endl;
		cin >> hh >> sep >> mm;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

