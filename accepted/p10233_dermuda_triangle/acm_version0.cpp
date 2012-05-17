/* @JUDGE_ID:  40922FK  10233  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10233 - Dermuda Triangle
 by: Francisco Dibar
 date: Nov-16-2005
**************************************************************************/

#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <string>
#include <cmath>			// sqrt
#include <iomanip>		// fixed

#define INVALID_CELL	-2
#define NOT_SET		-1

#define MAX			2147483647
#define SQRTMAX	46341	// sqrt(max)
#define DIM			16	// sqrt(max)


#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

using namespace std;

int vec_hex[DIM][DIM];	


///////////////////////////////////////////////////////////////////////////
void show_grid(bool hexagonal)
{
	for (int i = 0; i < DIM; i++) {
		if (hexagonal) {
			string s(i, ' ');
			cout << s;
		}
		for (int j = 0; j < DIM; j++) {
			if (vec_hex[i][j] == INVALID_CELL)
				cout << ". ";
			else
				cout << vec_hex[i][j] << " ";
		}
		cout << endl;
	}
}

///////////////////////////////////////////////////////////////////////////
void init_grid()
{
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++) 
			if (((i-j) % 3) == 0)
				vec_hex[i][j] = INVALID_CELL;
			else
				vec_hex[i][j] = NOT_SET;
}

///////////////////////////////////////////////////////////////////////////
double calc_distance(int n, int m)
{
	return 0;
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

//	vector<vector<int> > vec_hex(12);
	int n, m;
	cin >> n >> m;
	while (!cin.eof()) {
		// PROCESS
		init_grid();
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
	show_grid(true);
	cout << endl << endl;
	show_grid(false);
	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

