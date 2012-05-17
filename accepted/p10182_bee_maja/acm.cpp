/* @JUDGE_ID:  40922FK  10182  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10182 - Bee Maja
 by: Francisco Dibar
 date: Nov-13-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

using namespace std;

enum dirs { UPLEFT, UP, UPRIGHT, DOWNRIGHT, DOWN, DOWNLEFT };

///////////////////////////////////////////////////////////////////////////
void next(dirs dir, int *x, int *y)
{
	switch(dir) {
		case UPLEFT:	(*x)--; break;
		case UP:			(*y)--; break;
		case UPRIGHT:	(*x)++; (*y)--; break;
		case DOWNRIGHT:(*x)++; break;
		case DOWN:		(*y)++; break;
		case DOWNLEFT:	(*x)--; (*y)++; break;
	}
}
						
///////////////////////////////////////////////////////////////////////////
void convert(int n, int *x, int *y)
// convert hexagonal coordinates
{
	*x = 0;
	*y = 0;
	if (n <= 1) return;
	int ring = 1;
	int s = 2;
	next(DOWN, x, y);
	while (s < n) {
		// when entering new ring, go down left ring-1 times
		for (int i = 0; (i < ring-1) && (s < n); i++) {
			next(DOWNLEFT, x, y);
			s++;
		}
		if (s == n) return;
		// go up right, up, up left, down right and down, ring times each
		for (int d = UPLEFT; (d <= DOWN) && (s < n); d++) {
			for (int i = 0; (i < ring) && (s < n); i++) {
				next((dirs)d, x, y);
				s++;
			}
		}
		if (s == n) return;
		// go down, enter new ring
		next(DOWN, x, y);
		s++;
		ring++;
	}
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

	int n;
	cin >> n;
	while (!cin.eof()) {
		int x, y;
		// PROCESS
		convert(n, &x, &y);
		// SHOW OUTPUT
		cout << x << " " << y << endl;
		// READ NEXT INPUT
		cin >> n;
	}	
		
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

