/* @JUDGE_ID:  40922FK  10006  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10006 - Carmichael Numbers
 by: Francisco Dibar
 date: Nov-03-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <cmath>		// sqrt

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

using namespace std;

///////////////////////////////////////////////////////////////////////////
long modular_exponentiation(long a, long b, long n)
// returns a^b mod n
{
	long c = 0;
	long d = 1;
	const int BITS = 32;		// number of bits in b
	for (int i = BITS-1; i >= 0; i--) {
		c *= 2;
		d = (d * d) % n;
		long bit = 1 << i;
		bit &= b;
		if (bit > 0) {
			c =+ 1;
			d = (d * a) % n;
		}			
	}
	return d;
}

///////////////////////////////////////////////////////////////////////////
bool is_prime(long n)
{
	if (n <= 0)
		return false;

	if (n <= 3) 	// n > 0
		return true;

	if ((n % 2) == 0)
		return false;

	long i = 3;
	while (i < sqrt(n)+1) {
		if ((n % i) == 0) {
			return false;
		} else
			i += 2;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////
bool carmichael(long n)
{
	if (is_prime(n))
		return false;
	
	// for each 2 <= i < n, if a^n mod n = a then n is carmichael 
	// a^n mod n = (a mod n)^n mod n
	for (long a = 2; a < n; a++) {
		long r = modular_exponentiation(a, n, n);
		if (r != a)
			return false;
	}
	return true;
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
		if (carmichael(n))
			cout << "The number " << n << " is a Carmichael number." << endl;
		else
			cout << n << " is normal." << endl;
		cin >> n;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

