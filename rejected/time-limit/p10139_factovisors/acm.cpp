/* @JUDGE_ID:  40922FK  10139  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10139 - Factovisors
 by: Francisco Dibar
 date: Aug-16-2006
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 

#ifdef DEBUG
    #define START_DEBUG	"**************************** START DEBUG *****************************\n"
    #define END_DEBUG	"***************************** END DEBUG ******************************\n"
    // g++-2.95 doesn't support asserts
    #define ASSERT(x,y)   if (!(x)) { std::cerr << "ASSERTION FAILED!: " << y << "\n"; exit(1); }
#endif

using std::cin;
using std::cout;
using std::endl;

typedef long long int uint64;

///////////////////////////////////////////////////////////////////////////
bool divides(long m, long n)
// returns true if m divides n!    
{
    if (n >= m) {
        for (int i = n; i > 1; --i)
            if ((i % m) == 0) {
                return true;
            }
    }

    uint64 aux = n;
    for (int i = n-1; i > 1; --i) {
        aux *= i;
        aux %= m;
        if (aux == 0) {
            return true;
        }
    }
    return false;
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

	long n, m;
	cin >> n >> m;
    while (!cin.eof()) {
		// PROCESS & SHOW OUTPUT
#ifdef DEBUG
        cout << START_DEBUG;
#endif
        bool res = divides(m, n);
#ifdef DEBUG
        cout << END_DEBUG;
#endif
        if (res)
            cout << m << " divides " << n << "!" << endl;
        else
            cout << m << " does not divide " << n << "!" << endl;

		// READ NEXT INPUT
        cin >> n >> m;
	}
		
	return 0;
}

/* @END_OF_SOURCE_CODE */

