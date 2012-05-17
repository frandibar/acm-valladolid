/* @JUDGE_ID:  40922FK  10173  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10173 - Smallest Bounding Rectangle
 by: Francisco Dibar
 date: Nov-28-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <iomanip>		// fixed

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

	int points;
	cin >> points;
	while ((points != 0) && !cin.eof()) {
		// READ INPUT
		double x, y;
		double xmin, xmax, ymin, ymax;
		cin >> x >> y;
		xmin = xmax = x;
		ymin = ymax = y;
		for (int k = 1; k < points; k++) {
			cin >> x >> y;
			if (xmin > x) xmin = x;
			if (xmax < x) xmax = x;
			if (ymin > y) ymin = y;
			if (ymax < y) ymax = y;
		}

		// PROCESS
		double area = (xmax - xmin) * (ymax - ymin);

		// SHOW OUTPUT
		cout.setf(ios::fixed);
		cout.precision(4);
		cout << area << endl;

		// READ NEXT INPUT
		cin >> points;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

