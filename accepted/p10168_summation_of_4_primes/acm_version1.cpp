/* @JUDGE_ID:  40922FK  10168  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10168 - Summation of Four Primes
 by: Francisco Dibar
 date: Nov-07-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <cmath>			// sqrt
#include <algorithm>		// binary_search

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
bool is_prime(int64 n)
{
	if (n <= 1)
		return false;

	if (n <= 3) 	// n > 1
		return true;

	if ((n % 2) == 0)
		return false;

	int64 i = 5;
	while (i < sqrt((double)n)+1) {
		if ((n % i) == 0) {
			return false;
		} else
			i += 2;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////
void calculate_primes(long n, vector<int64>& v)
// fill v with first n primes
{
	// warning: assuming n > 2
	v[0] = 2;
	v[1] = 3;
	long count = 2;
	int i = 5;
	while (count < n) {
		if (is_prime(i))
			v[count++] = i;
		i += 2;
	}		
}

///////////////////////////////////////////////////////////////////////////
bool find_2_primes(int64 n, vector<int64>& vec_primes, int64 *p1, int64 *p2)
// return true if 2 primes are found p1 and p2 such that n = p1 + p2
{
	long i = 0;
	bool found = false;
	while (!found && (vec_primes[i] < n)) {
		*p1 = vec_primes[i];
		*p2 = n - *p1;
		if (binary_search(vec_primes.begin(), vec_primes.end(), *p2))
			found = true;
		else
			i++;
	}
	return found;
}

///////////////////////////////////////////////////////////////////////////
bool find_prime_sum(int64 n, vector<int64>& vec_primes, vector<int64>& vec_sum)
// returns true if n can be expressed as a sum of 4 primes, left in v
{
	// even = even + even
	// even = odd + odd
	// odd = odd + even
	
	// waring's conjecture
	// odd = prime 
	// odd = prime + prime + prime
	
	// goldbachs's conjecture
	// even = prime + prime

	// solving method:	
	
	// if n < 4 return false
	// if n is even, divide by 2
	// n = d + d
	// if dividend d is even, find 2 primes 
	// e = p1 + p2
	// result: p1 p2 p1 p2
	// if dividend d is odd, obtain sum of primes for d-1(even) and d+1(even)
	// n = d-1 + d+1
	// result: p1 p2 p3 p4

	// if n is odd, then n = n-2(odd) + d
	// find sum of 3 primes for n-2 = 2 + p1 + p2 or n-2 = 3 + p1 + p2

	// always try to find the biggest and smallest primes to sum
	// ej, 14 = 13 + 1 instead of 11 + 3
	if (n < 8)
		return false;

	int64 p1, p2;
	if ((n % 2) == 0) {
		// n even
		int64 d = n / 2;
		if ((d % 2) == 0) {
			// d even
			if (find_2_primes(d, vec_primes, &p1, &p2)) {
				vec_sum[0] = vec_sum[1] = p1;
				vec_sum[2] = vec_sum[3] = p2;
				return true;
			} else
				return false;	// should NEVER get here
		} else {
			// d odd
			if (find_2_primes(d-1, vec_primes, &p1, &p2)) {
				vec_sum[0] = p1;
				vec_sum[1] = p2;
				if (find_2_primes(d+1, vec_primes, &p1, &p2)) {
					vec_sum[2] = p1;
					vec_sum[3] = p2;
					return true;
				} else
					return false;	// should NEVER get here
			} else
				return false;	// should NEVER get here
		}
	} else {
		// n odd
		vec_sum[0] = 2;
		if (find_2_primes(n-4, vec_primes, &p1, &p2)) {
			vec_sum[1] = 2;
			vec_sum[2] = p1;
			vec_sum[3] = p2;
			return true;
		} else if (find_2_primes(n-5, vec_primes, &p1, &p2)) {
			vec_sum[1] = 3;
			vec_sum[2] = p1;
			vec_sum[3] = p2;
			return true;
		} else
			return false;	// should NEVER get here
	}
	return true;	// should NEVER get here
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

	// REVISAR: tarda demasiado en calcular los primos!!
	// another aproach is not using precalculated primes

//	const long MAX = 664590; // 664580;
	const long MAX = 50000;
	vector<int64> vec_primes(MAX);
	// precalculate first MAX primes
	calculate_primes(MAX, vec_primes);

	int64 n;
	cin >> n;
	while (!cin.eof()) {
		// PROCESS & SHOW OUTPUT
		vector<int64> vec_sum(4);
		if (find_prime_sum(n, vec_primes, vec_sum)) {
			for (int i = 0; i < 3; i++)
				cout << vec_sum[i] << " ";
			cout << vec_sum[3] << endl;
		} else
			cout << "Impossible." << endl;

		// READ NEXT INPUT
		cin >> n;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;
	// print vec_primes
	for (long i = 0; i < MAX; i++)
		cout << vec_primes[i] << endl;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

