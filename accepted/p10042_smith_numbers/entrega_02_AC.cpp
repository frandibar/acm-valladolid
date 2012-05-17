/* @JUDGE_ID:  40922FK  10042  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10042 - Smith Numbers
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
int add_digits(long n)
// returns the sum of n's digits
{
	int sum = 0;
	if (n < 10)
		return n;
	else {
		while (n >= 10) {
			sum += n % 10;
			n /= 10;
		}
	}
	return sum + n;
}

///////////////////////////////////////////////////////////////////////////
long sum_digits_prime_factors(long x)
// returns the sum of the digits of the prime factors of x
{
	if (x == 0) return 0;

	long sum = 0;
	long c = x;
	while ((c % 2) == 0) {
		sum += 2;
		c /= 2;
	}

	long i = 3;
	while (i < (sqrt(x)+1)) {
		if ((c % i) == 0) {
			sum += add_digits(i);
			c /= i;
		} else
			i += 2;
	}
	if (c > 1)
		sum += add_digits(c);

	return sum;
}

///////////////////////////////////////////////////////////////////////////
long next_smith_number(long n)
// returns next smith number >= n
{
	long next = n+1;
	while (is_prime(next))
		next++;
	long s = add_digits(next);
	long p = sum_digits_prime_factors(next);
	while (s != p) {
		next++;
		while (is_prime(next))
			next++;
		s = add_digits(next);
		p = sum_digits_prime_factors(next);
	}
	return next;
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

	int cases;
	cin >> cases;
	for (int k = 0; (k < cases) && !cin.eof(); k++) {
		long n;
		// READ INPUT
		cin >> n;
		// PROCESS
		long s = next_smith_number(n);
		// SHOW OUTPUT
		cout << s << endl;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

