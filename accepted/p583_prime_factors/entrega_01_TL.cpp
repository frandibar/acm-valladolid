/* @JUDGE_ID:  40922FK  583  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 583 - Prime Factors
 by: Francisco Dibar
 date: Oct-26-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <cmath>

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

using namespace std;

///////////////////////////////////////////////////////////////////////////
void print_prime_factors(long x)
// returns the prime factors of x in the format p1 x p2 x .. x pn
{
	cout << x << " = ";
	bool first = false;

	if (x == 0) {
		cout << "0" << endl;
		return;
	}
	if (x < 0) {
		cout << "-1";
		x *= -1;
		first = true;
	}

	long c = x;
	while ((c % 2) == 0) {
		if (first) cout << " x ";
		cout << "2";
		c /= 2;
		first = true;
	}

	long i = 3;
	while (i < (sqrt(x)+1)) {
		if ((c % i) == 0) {
			if (first) cout << " x ";
			cout << i;
			c /= i;
			first = true;
		} else
			i += 2;
	}
	if (c > 1) {
		if (first) cout << " x ";
		cout << c;
	}
	cout << endl;
	return;
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

	long n;
	cin >> n;
	while ((n != 0) && !cin.eof()) {
		print_prime_factors(n);
		cin >> n;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

