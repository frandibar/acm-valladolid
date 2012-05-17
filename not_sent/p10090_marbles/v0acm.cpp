/* @JUDGE_ID:  40922FK  10090  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10090 - Marbles
 by: Francisco Dibar
 date: Nov-04-2005
**************************************************************************/

#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
    #include <fstream>
#endif 
#include <cmath>

#ifdef DEBUG
    #define START_DEBUG	"START DEBUG ********************************************************************\n"
    #define END_DEBUG	"END DEBUG **********************************************************************\n"
    // g++-2.95 doesn't support asserts
    #define ASSERT(x,y)   if (!(x)) { std::cerr << "ASSERTION FAILED!: " << y << "\n"; exit(1); }
#endif

using std::cin;
using std::cout;
using std::endl;

typedef unsigned long ulong;

// TODO: find an iterative solution to improve speed
///////////////////////////////////////////////////////////////////////////
inline unsigned long gcd(unsigned long p, unsigned long q)
{
    if (q > p) 
        return gcd(q, p);

    if (q == 0)
        return p;

    return gcd(q, p%q);
}

///////////////////////////////////////////////////////////////////////////
unsigned long gcd(unsigned long p, unsigned long q, long *x, long *y)
// returns the gcd(p,q) and x,y such that p*x + q*y = gcd(p,q)    
// extended gcd    
{
    if (q > p) 
        return gcd(q, p, y, x);

    if (q == 0) {
        *x = 1;
        *y = 0;
        return p;
    }

    long x1, y1;
    unsigned long g;
    g = gcd(q, p%q, &x1, &y1);
    *x = y1;
    *y = (x1 - (long)std::floor(p/q) * y1);
    return g;
}

///////////////////////////////////////////////////////////////////////////
bool solve(ulong nmarbles, ulong c1, ulong n1, ulong c2, ulong n2, long *aOut, long *bOut)
// returns true if a solution is found, and output in aOut and bOut    
// ci cost of box i
// ni size of box i
// aOut amount of box1
// bOut amount of box2
{
    // see p.155 Programming challenges
    // x eq a1 (mod m1) and x eq a2 (mod m2)
    // => x  is uniquely determined (mod m1*m2) if m1 and m2 are relatively prime
    // if not, perhaps multiple solutions exist
    // solve linear congruences 
    // m2*b1 eq 1 (mod m1)
    // m1*b2 eq 1 (mod m2)
    // such that x = a1*b1*m2 + a2*b2*m1

    // nmarbles eq n1 (mod n2) and nmarbles eq n2 (mod n1)
    if (((nmarbles - n1) % n2 != 0) || ((nmarbles - n2) % n1 != 0))
        return false;

    int b1 = 1,
        b2 = 1;
    int res = n2 * b1 - 1;
    while ((double)res / n1 != 0) {
        b1++;
        res = n2 * b1 - 1;
    }
    res = n1 * b2 - 1;
    while ((double)res / n2 != 0) {
        b2++;
        res = n1 * b2 - 1;
    }
    
    ulong a1 = nmarbles % n1;
    ulong a2 = nmarbles % n2;
    ulong s = gcd(a1 * n2, a2 * n1, aOut, bOut);
#ifdef DEBUG
    cout << "gcd: " << a1 << " " << a2 << endl;
#endif
    if (s != nmarbles)
        return false;

    return true;

    double p1 = (double)c1 / n1;    // cost per marble
    double p2 = (double)c2 / n2;
    // buy more boxes that cost less per marble
    // gcd = (a + k n2/d) n1/d + (b - k n1/d) n2/d
    int k = 0;
    int sign = 1;
    if (p1 > p2)
        sign = -1;

    while ((*aOut < 0) || (*bOut < 0)) {
        k++;
        *aOut += sign * k * n2;
        *bOut -= sign * k * n1;
    }
    return true;    
}   


///////////////////////////////////////////////////////////////////////////
//	MAIN PROGRAM
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redirect input and output
#ifndef ONLINE_JUDGE 
    cin.rdbuf((new std::ifstream("input"))->rdbuf()); 
    cout.rdbuf((new std::ofstream("output"))->rdbuf()); 
#endif 

    ulong nmarbles;
    cin >> nmarbles;
    while ((nmarbles != 0) && !cin.eof()) {
        // READ INPUT
        ulong c1, c2, n1, n2;
        cin >> c1 >> n1 >> c2 >> n2;

#ifdef DEBUG
        cout << START_DEBUG;
        cout << "solving for " << nmarbles << " marbles, c1 = " << c1 << ", n1 = " << n1 << ", c2 = " << c2 << ", n2 = " << n2 << endl;
#endif
        // PROCESS
        long a, b;
        bool sol = solve(nmarbles, c1, n1, c2, n2, &a, &b);

#ifdef DEBUG
        cout << END_DEBUG;
#endif

        // SHOW RESULTS
        if (sol)
            cout << a << " " << b << endl;
        else
            cout << "failed" << endl;  

        // READ NEXT INPUT
        cin >> nmarbles;
    }
    
    return 0;
}

/* @END_OF_SOURCE_CODE */

// Method to solve: Chineese remainder theorem
