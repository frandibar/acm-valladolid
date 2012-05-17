/* @JUDGE_ID:  40922FK  10110  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10110 - Light, more Light
 by: Francisco Dibar
 date: Oct-25-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <cmath>

#define START_DEBUG	"START DEBUG *******************************************************************\n"
#define END_DEBUG	"END DEBUG *********************************************************************\n"


using namespace std;

///////////////////////////////////////////////////////////////////////////
int num_divisors(long long x)
// returns the amount of divisors of x
// uses prime factorization algorithm
{
	#ifdef DEBUG
	cout << START_DEBUG;
	cout << "divisors of " << x << endl;
	#endif	
	
	long long c = x;
	int n = 1;
	while ((c % 2) == 0) {
		#ifdef DEBUG
		cout << '2' << endl;
		#endif	
		c /= 2;
		n++;
	}
	long i = 3;
	while (i <= (sqrt(c)+1)) {
		if ((c % i) == 0) {
			#ifdef DEBUG
			cout << i << endl;
			#endif	
			c /= i;
			n++;
		} else
			i += 2;
	}
	if (c > 1) {
		#ifdef DEBUG
		cout << c << endl;
		#endif	
		n++;
	}
	
	#ifdef DEBUG
	cout << '1' << endl;
	cout << END_DEBUG;
	#endif

	return n;
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

	long long n;
	cin >> n;
	while (n && !cin.eof()) {
		// PROCESS
		int res = num_divisors(n);
		
		#ifdef DEBUG
		cout << START_DEBUG;
		cout << n << " has " << res << " divisors " << endl;
		cout << END_DEBUG;
		#endif
		
		// SHOW OUTPUT
		cout << ((res % 2 != 0) ? "yes" : "no") << endl;
		// READ NEXT INPUT
		cin >> n;
	}
		
	return 0;
}

/* @END_OF_SOURCE_CODE */

