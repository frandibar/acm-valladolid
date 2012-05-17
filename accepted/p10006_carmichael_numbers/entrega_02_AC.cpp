/* @JUDGE_ID:  40922FK  10006  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10006 - Carmichael Numbers
 by: Francisco Dibar
 date: Nov-04-2005
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

// The base types 
#ifdef WIN32 
	typedef __int8            		int8; 
	typedef __int16           		int16; 
	typedef __int32           		int32; 
	typedef __int64           		int64; 
	typedef unsigned __int8   		uint8; 
	typedef unsigned __int16  		uint16; 
	typedef unsigned __int32  		uint32; 
	typedef unsigned __int64  		uint64; 
#else 
	typedef char                    int8; 
	typedef short                   int16; 
	typedef long                    int32; 
	typedef long long int           int64; 
	typedef unsigned char           uint8; 
	typedef unsigned short          uint16; 
	typedef unsigned long           uint32; 
	typedef unsigned long long int  uint64; 
#endif 


using namespace std;

///////////////////////////////////////////////////////////////////////////
int64 modular_exponentiation(int64 a, int64 b, int64 n)
// returns a^b mod n
{
	int64 c = 0;
	int64 d = 1;
	const int BITS = 32;		// number of bits in b
	for (int i = BITS-1; i >= 0; i--) {
		c *= 2;
		d = (d % n) * (d % n) % n;		// d = (d * d) % n;
		int64 bit = 1 << i;
		bit &= b;
		if (bit > 0) {
			c =+ 1;
			d = (d % n) * (a % n) % n;		// d = (d * a) % n;
		}			
	}
	return d;
}

///////////////////////////////////////////////////////////////////////////
bool is_prime(int64 n)
{
	if (n <= 0)
		return false;

	if (n <= 3) 	// n > 0
		return true;

	if ((n % 2) == 0)
		return false;

	int64 i = 3;
	while (i < (int64)sqrt((double)n)+1) {
		if ((n % i) == 0) {
			return false;
		} else
			i += 2;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////
bool carmichael(int64 n)
{
	if (is_prime(n))
		return false;
	
	// for each 2 <= i < n, if a^n mod n = a then n is carmichael 
	// a^n mod n = (a mod n)^n mod n
	for (int64 a = 2; a < n; a++) {
		int64 r = modular_exponentiation(a, n, n);
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

	// The first 15 Carmichael numbers are:
	// 561,1105,1729,2465,2821,6601,8911,10585,15841,
	//	29341,41041,46657,52633,62745,63973

	int64 n;
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
		for (int n = 2; n < 65000; n++)
			if (carmichael(n))
				cout << "The number " << n << " is a Carmichael number." << endl;
		cout << END_DEBUG;
	#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

