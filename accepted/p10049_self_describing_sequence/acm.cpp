/* @JUDGE_ID:  40922FK  10049  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10049 - Self-describing Sequence
 by: Francisco Dibar
 date: Jul-28-2006
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"
// g++-2.95 doesn't support asserts
#define ASSERT(x,y)   if (!(x)) { std::cerr << "ASSERTION FAILED!: " << y << "\n"; exit(1); }

using std::cin;
using std::cout;
using std::endl;
using std::vector;

const long DIM = 700000;

long vInvF[DIM];    // vInvF[0] stores the precomputed values
                    // it's the inverse function

///////////////////////////////////////////////////////////////////////////
long f(long n)
{
    // use binary search
    long i = 0, j = vInvF[0];
    while (i <= j) {
        long m = (i + j) / 2;   // TODO: watch out for overflow
        if (vInvF[m] == n)
            return m;
        else if ((vInvF[m] > n) && (vInvF[m-1] <= n))
            return m-1;
        else if (vInvF[m] > n)
            j = m - 1;
        else
            i = m + 1;
    }

    ASSERT(false, "f(n) not found");
    return -1;  // should never get here
}


///////////////////////////////////////////////////////////////////////////
void initvInfF()
// initialize array of precalculated values
{
    // f(vInvF[k]) = ... = f(vInvF[k+1]-1) = k
    vInvF[1] = 1;
    vInvF[2] = 2;
    vInvF[3] = 4;
    vInvF[4] = 6;
    vInvF[5] = 9;
    vInvF[6] = 12;

    vInvF[0] = 6;   // # of precalculated values
}

///////////////////////////////////////////////////////////////////////////
void precomputeValues(long n)
// calculate values so as to be able to obtain f(n)
{
    for (long i = vInvF[0]; vInvF[i] < n; ++i) {
        vInvF[i+1] = vInvF[i] + f(i);   // calculate upper bound 
        vInvF[0]++;   // increment precalculated values
    }
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

    long n;
	cin >> n;
    initvInfF();        // initialize array of precomputed values
    while (n != 0) {
		// PROCESS AND SHOW OUTPUT
        precomputeValues(n);
#ifdef DEBUG
        cout << "f(" << n << ") =\t";
#endif
        cout << f(n) << endl;

		// READ NEXT INPUT
        cin >> n;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;
    for (int i = 1; i < vInvF[0]; ++i)
        cout << "f(" << vInvF[i] << ") = ... = f(" << vInvF[i+1]-1 << ") =\t" << i << endl;
	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

