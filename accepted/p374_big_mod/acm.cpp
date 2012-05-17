/* @JUDGE_ID:  40922FK  374  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 374 - Big Mod
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
    #define START_DEBUG "START DEBUG ********************************************************************\n"
    #define END_DEBUG   "END DEBUG **********************************************************************\n"
    // g++-2.95 doesn't support asserts
    #define ASSERT(x,y)   if (!(x)) { std::cerr << "ASSERTION FAILED!: " << y << "\n"; exit(1); }
#endif

using std::cin;
using std::cout;
using std::endl;

typedef unsigned long long int  uint64;

////////////////////////////////////////////////////////////////////////////////
uint64 modularExp(uint64 a, uint64 b, uint64 n)
// perform the modular exponentiation    
// returns a^b mod n = (a mod n)^b mod n
// Method to solve: raising to powers with repeated squaring
// see Introduction to algorithms - Cormen p.879    
{
    uint64 aux = 1;
    while (b > aux)
        aux <<= 1;

#ifdef DEBUG
    cout << "calculating " << a << "^" << b << " mod " << n << endl;
#endif

    if (b < aux) aux >>= 1;
    //uint64 c = 0;         // used for debugging only
    uint64 d = 1;
    while (aux > 0) {
        //c *= 2;
        d *= d;
        d %= n;
        if ((aux & b) == aux) {
            //c++;
            d *= a;
            d %= n;
        }
#ifdef DEBUG
        cout << "bi = " << (((aux & b) == aux) ? 1 : 0) << "\tc = " << c << "\td = " << d << endl;
#endif
        aux >>= 1;
    }
    return d;
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

    // xy mod n = (x mod n)(y mod n) mod n    
    // b^p mod m = (b mod m)^p mod m
    uint64 b, p, m;
    cin >> b >> p >> m;
    while (!cin.eof()) {

#ifdef DEBUG
        cout << START_DEBUG;
#endif
        // PROCESS
        uint64 res = modularExp(b, p, m);

#ifdef DEBUG
        cout << END_DEBUG;
#endif

        // SHOW OUTPUT
        cout << res << endl;

        // READ NEXT INPUT
        cin >> b >> p >> m;
    }

    return 0;
}

/* @END_OF_SOURCE_CODE */

