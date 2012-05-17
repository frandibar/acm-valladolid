/* @JUDGE_ID:  40922FK  10139  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10139 - Factovisors
 by: Francisco Dibar
 date: Nov-05-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <cmath>		// sqrt
#include <vector>

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
long prime_factors(int64 x, vector<int64>& v)
// adds x's prime factors into v, and returns the amount of them
// does not add prime number 1
{
	long primes = 0;
	while ((x % 2) == 0) {
		v.push_back(2);
		primes++;
		x /= 2;
	}

	long i = 3;
	while (i < (sqrt((double)x)+1)) {
		if ((x % i) == 0) {
			v.push_back(i);
			primes++;
			x /= i;
		} else
			i += 2;
	}
	if (x > 1) {
		v.push_back(x);
		primes++;
	}
	return primes;
}

///////////////////////////////////////////////////////////////////////////
bool factovisors(int64 n, int64 m)
// returns true if m | n!  ->  n! % m = 0
{
	// a.b mod n = (a mod n) . (b mod n) mod n
	// (a+b) mod n = (a mod n) + (b mod n) mod n

	// n! % m = n.(n-1)...1 % m 
	//	       = (n % m).(n-1 % m)...(1 % m) % m
	// factorize n, n-1, etc and apply the same formula
	//        = (p1.p2..pk % m).(p1.p2..pk-1 % m)...(1 % m)
	// let p = ((p1%m).(p2%m)...(pk%m))%m
	// n! % m = (p%m . (p%m - 1%m )%m . (p%m - 2%m )%m ..
/*
	// version 1
	int64 res = 1;
	for (int64 i = n; i > 0; i--)
		res *= i % m;		// grows too much!!
	
	return ((res % m) == 0);

*/
	// version 2
	int64 res = 1;
	for (int64 i = n; i > 0; i--) {
		vector<int64> v;
		long p = prime_factors(i, v);
		// calculate (p1.p2..pk % m)
		int64 s = 1;
		for (int j = 0; j < (int)v.size(); j++) {
			s *= v[j] % m;
		}
		s %= m;
		res *= s % m;		// grows too much!!
	}
	return ((res % m) == 0);
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

	int64 n, m;
	cin >> n >> m;
	while (!cin.eof()) {
		if (factovisors(n,m))
			cout << m << " divides " << n << "!" << endl;
		else
			cout << m << " does not divide " << n << "!" << endl;

		cin >> n >> m;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

