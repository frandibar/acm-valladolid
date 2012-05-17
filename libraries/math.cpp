/*

DIVISIBILITY

any number divisible by two if last digit is divisible by two.
any number divisible by 3 if sum of digits is divisible by 3.
any number divisible by 5 if last digit is 0 or 5.
any number divisible by 11 if sum of it's even digits and sum of it's
odd digits are equal.
ex: 692863963 is divisible by 11.
6 + 2 + 8 + 9 + 3 = 26
9 + 8 + 3 + 6 = 26
any number divisible by 4 if last two digit is divisible by 4. 

 */

///////////////////////////////////////////////////////////////////////////
long gcdExtended(long p, long q, long *x, long *y)
{
	if (q > p) 
		return gcd(q, p, y, x);

	if (q == 0) {
		*x = 1;
		*y = 0;
		return p;
	}

	long x1, y1, g;
	g = gcd(q, p%q, &x1, &y1);
	*x = y1;
	*y = (x1 - floor(p/q) * y1);
	return g;
}

///////////////////////////////////////////////////////////////////////////
long gcd(long p, long q)
{
	if (q > p) 
		return gcd(q, p);

	if (q == 0)
		return p;

	return gcd(q, p%q);
}


///////////////////////////////////////////////////////////////////////////
bool isPrime(long n)
{
	if (n <= 1)
		return false;

	if (n <= 3) 	// n > 1
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
long modularExponentiation(long a, long b, long n)
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
#include <cmath>    // sqrt
void primeFactors(long n, vector<long>& vFactors)
// adds n's prime factors into vFactors
{
	while ((n % 2) == 0) {
		vFactors.push_back(2);
		n /= 2;
	}

	long i = 3;
    double root = std::sqrt((double)n);
	while (i < root + 1) {
		if ((n % i) == 0) {
			vFactors.push_back(i);
			n /= i;
            root = std::sqrt((double)n);
		} else
			i += 2;
	}
	if (n > 1)
		vFactors.push_back(n);
}

