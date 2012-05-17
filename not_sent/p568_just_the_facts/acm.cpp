/* @JUDGE_ID:  40922FK  568  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 568 - Just the Facts
 by: Francisco Dibar
 date: Mar-24-2005
**************************************************************************/

#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
    #include <fstream>
#endif 
#include <iomanip>  // setw
#include <vector>

#ifdef DEBUG
    #define START_DEBUG "START DEBUG ********************************************************************\n"
    #define END_DEBUG   "END DEBUG **********************************************************************\n"
    // g++-2.95 doesn't support asserts
    #define ASSERT(x,y)   if (!(x)) { std::cerr << "ASSERTION FAILED!: " << y << "\n"; exit(1); }
#endif

using std::cin;
using std::cout;
using std::endl;
using std::vector;

typedef unsigned long long int uint64;

////////////////////////////////////////////////////////////////////////////////
unsigned int factLastDigit(unsigned int n)
// return last non-zero digit of n!    
{
    if (n == 0) return 1;

    // n! mod d = [(n mod d)(n-1 mod d)...(1 mod d)] mod d
    int d = 10;
    uint64 res = 1;
    for (unsigned int i = 2; i <= n; ++i) {
#ifdef DEBUG
        cout << "res = " << res << "\t\ti = " << i << endl;
#endif            
        res *= i;
        while ((res % d) == 0)
            res /= 10;
    }
    return res % 10;
}

///////////////////////////////////////////////////////////////////////////
//  MAIN PROGRAM
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    // redirect input and output
    #ifndef ONLINE_JUDGE 
        cin.rdbuf((new std::ifstream("input"))->rdbuf()); 
        cout.rdbuf((new std::ofstream("output"))->rdbuf()); 
    #endif 

    unsigned int n;
    cin >> n;
    while (!cin.eof()) {

#ifdef DEBUG
        cout << START_DEBUG;
        cout << "calculating for n = " << n << endl;
#endif
        // PROCESS
        unsigned int res = factLastDigit(n);

#ifdef DEBUG
        cout << END_DEBUG;
#endif
        // SHOW OUTPUT
        cout << setw(5) << n << " -> " << res << endl;

        // READ NEXT INPUT
        cin >> n;
    }

    return 0;
}

/* @END_OF_SOURCE_CODE */

