/* @JUDGE_ID:  40922FK  374  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 374 - Big Mod
 by: Francisco Dibar
 date: Aug-14-2006
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
uint64 powerMod(uint64 b, uint64 p, uint64 m)
// returns b^p mod m = (b mod m)^p mod m    
{
#ifdef DEBUG
    cout << "calculating " << b << "^" << p << " mod " << m << endl;
#endif
    uint64 res;   // stores the result

    if (p < 3) {
        uint64 aux = b % m;
        res = aux;
        for (int i = 0; i < (int)p - 1; ++i)
            res *= aux;
        res %= m;
#ifdef DEBUG
        cout << b << "^" << p << " mod " << m << " = " << res << endl;
#endif
        return res;
    }

    uint64 power = 3;
    uint64 aux = b % m;
    res = (aux * aux * aux) % m;   // b ^ power mod m
#ifdef DEBUG
    cout << b << "^" << power << " mod " << m << " = " << res << endl;
#endif
    while (p >= 2 * power) {
        res *= res;
        res %= m;
        power *= 2;
#ifdef DEBUG
        cout << b << "^" << power << " mod " << m << " = " << res << endl;
#endif
    }
    uint64 r = p - power;
    if (r != 0) {
#ifdef DEBUG
        cout << "----> " << r << " remains" << endl;
#endif
        uint64 aux1 = powerMod(b, r, m);
        uint64 aux2 = (res * aux1) % m;
#ifdef DEBUG
        cout << res <<  " x " << aux1 << " mod " << m << " = " << aux2 << endl;
#endif
        return aux2;
    }

    return res % m;
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
        uint64 res = powerMod(b, p, m);

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

