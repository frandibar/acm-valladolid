/* @JUDGE_ID:  40922FK  846  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 846 - Steps
 by: Francisco Dibar
 date: Jul-27-2006
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

///////////////////////////////////////////////////////////////////////////
long solve(long a, long b)
{
    long L = b - a;
    if (L <= 2) return L;

    long nsteps = 0;
    int size = 1; 
    while (L > 0) {
        if (L > 3 * size) {
            L -= 2 * size;
            size++;
            nsteps += 2;
        } else if ((L == 3 * size) || (L == 3 * size - 1)) {
            L = 0;
            nsteps += 3;
        } else if ((L == 2 * size) || (L == 2 * size - 1)) {
            L = 0;
            nsteps += 2;
        } else if (L == size) {
            L = 0;
            nsteps += 1;
        } else 
            size--;
    }
#ifdef DEBUG
    ASSERT(L == 0, "L == 0");
#endif
    return nsteps;
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
    
	int cases;
	cin >> cases;

	for (int k = 0; k < cases; k++) {
        long a, b;
		// READ INPUT
        cin >> a >> b;

		// PROCESS
#ifdef DEBUG
        cout << b-a << ":\t";
#endif
        long steps = solve(a, b);

		// SHOW OUTPUT
        cout << steps << endl;

	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */
