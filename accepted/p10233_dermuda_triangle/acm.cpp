/* @JUDGE_ID:  40922FK  10233  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10233 - Dermuda Triangle
 by: Francisco Dibar
 date: Nov-16-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <cmath>			// sqrt
#include <iomanip>		// fixed

#define TAN30	0.57735026919

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

using namespace std;


///////////////////////////////////////////////////////////////////////////
void get_coords(int n, double *xn, double *yn)
{
	// obtain row in which number appears
	int row = (int)sqrt(n);
	int offset = n - row * row;		// offset in row

//	int t = 2 * row + 1;					// triangles in row
//	*yn = 0.5 * (offset - (t+1)/2 + 1);
	*yn = 0.5 * (offset - row);		// simplified

	// calculate xn, yn
	if (n % 2 == 0) {
		if (row % 2 == 0) {
			*xn = (row+1) * sqrt(3) / 2.0 - TAN30 / 2.0;
		} else {
			*xn = row * sqrt(3) / 2.0 + TAN30 / 2.0;
		}
	} else {
		if (row % 2 == 0) {
			*xn = row * sqrt(3) / 2.0 + TAN30 / 2.0;
		} else {
			*xn = (row+1) * sqrt(3) / 2.0 - TAN30 / 2.0;
		}
	}
}

///////////////////////////////////////////////////////////////////////////
double calc_distance(int n, int m)
{
	double xn, yn, xm, ym;
	get_coords(n, &xn, &yn);
	get_coords(m, &xm, &ym);

#ifdef DEBUG
	cout << START_DEBUG;
	cout << "(" << xn << "," << yn << ") - (" << xm << "," << ym << ")" << endl; 
	cout << END_DEBUG;
#endif
	
	double lx = xn - xm;
	double ly = yn - ym;
	return sqrt(lx*lx + ly*ly);
}

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

	int n, m;
	cin >> n >> m;
	while (!cin.eof()) {
		// PROCESS
		double d = calc_distance(n, m);

		// SHOW OUTPUT
		cout.setf(ios::fixed);
		cout.precision(3);
		cout << d << endl;

		// READ NEXT INPUT
		cin >> n >> m;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;
	
	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

