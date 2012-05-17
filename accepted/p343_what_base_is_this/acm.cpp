/* @JUDGE_ID:  40922FK  343  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 343 - What Base is This?
 by: Francisco Dibar
 date: Mar-15-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
    #include <fstream>
#endif 
#include <algorithm>    // swap
#include <string>

#ifdef DEBUG
    #define START_DEBUG "**************************** START DEBUG *****************************\n"
    #define END_DEBUG   "***************************** END DEBUG ******************************\n"
    // g++-2.95 doesn't support asserts
    #define ASSERT(x,y)   if (!(x)) { std::cerr << "ASSERTION FAILED!: " << y << "\n"; exit(1); }
#endif

using std::cin;
using std::cout;
using std::endl;
using std::string;

const int MAX_BASE = 36;

typedef unsigned long long int uint64;

///////////////////////////////////////////////////////////////////////////
string decimalToBase(uint64 num, int base)
// converts num from decimal to base base
// precondition: base <= MAX_BASE
{
    // consider special cases
    if ((base < 2) || (base > MAX_BASE)) return "0";
    if (num == 0) return "0";
    
    string out;
    long aux = num;
    while (aux > 0) {
        int remainder = aux % base;
        if (remainder <= 9)
            out += remainder + '0';
        else
            out += remainder - 10 + 'A';
        aux /= base;
    }

    // reverse out
    for (int i = 0; i < ((int)out.length()) / 2; ++i)
        std::swap(out[i], out[out.length() - i - 1]);

    return out;
}

///////////////////////////////////////////////////////////////////////////
uint64 toUInt(const string& num)
// returns num as an int
// precondition: num is an unsigned number, expressed in base 10
{
    uint64 out = 0,
           weight = 1;
    
    for (int i = num.length() - 1; i >= 0; --i) {
        out += weight * (num[i] - '0');
        weight *= 10;
    }
    return out;
}

///////////////////////////////////////////////////////////////////////////
uint64 baseToDecimal(const string& num, int base)
// returns num expressed in base base converted to decimal    
// precondition: base <= MAX_BASE
{
    // special cases
    if (base == 10) return toUInt(num);
    if (base > MAX_BASE) return 0;
    
    uint64 out = 0,
           bn = 1;
    for (int i = (int)num.length() - 1; i >= 0; --i) {
        if (num[i] <= '9') 
            out += bn * (num[i] - '0');
        else
            out += bn * (num[i] - 'A' + 10);
        bn *= base;
    }
    return out;
}

///////////////////////////////////////////////////////////////////////////
bool baseOk(const string& num, int base)
// return true if num is correctly expressed in base base    
{
    // if any digit in num is greater or equal to base then return false
    int b = ((base <= 9) ? base + '0' : base + 'A' - 10);

    for (int i = 0; i < (int)num.length(); i++)
        if (num[i] >= b)
            return false;

    return true;
}

///////////////////////////////////////////////////////////////////////////
int minimumBase(const string& num)
// returns minimum base in which num can be expressed    
{
    // find highest digit
    int base = 0;
    for (int i = 0; i < (int)num.length(); i++) {
        if (num[i] > base)
            base = num[i];
    }
    // convert from char to int
    if (base > '9') 
        base += 11 - 'A';
    else
        base += 1 - '0';
    
    return ((base == 1) ? 2 : base);
}

///////////////////////////////////////////////////////////////////////////
inline string changeBase(const string& num, int b1, int b2)
// return num in base b1 expressed as base b2
// precondition: num is correctly expressed in base b1
{
    // convert from b1 to decimal, and from decimal to b2
    return (decimalToBase(baseToDecimal(num, b1), b2));
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

    string x, y;
    // READ INPUT
    cin >> x >> y;
    while (!cin.eof()) {

        // PROCESS
        int bx = minimumBase(x);
        int by = minimumBase(y);
        uint64 dx = toUInt(changeBase(x, bx, 10));
        uint64 dy = toUInt(changeBase(y, by, 10));

#ifdef DEBUG
        cout << START_DEBUG;
        cout << "solving for\tx = " << x << "\ty = " << y << endl;
        cout << "\t\tx (base " << bx << ") = " << dx << "\t\ty (base " << by << ") = " << dy << endl;
#endif

        while ((dx != dy) && (bx <= MAX_BASE) && (by <= MAX_BASE)) {
            if (dx < dy) {
                bx++;
                dx = toUInt(changeBase(x, bx, 10));
            } else {
                by++;
                dy = toUInt(changeBase(y, by, 10));
            }
#ifdef DEBUG
            cout << "\t\tx (base " << bx << ") = " << dx << "\t\ty (base " << by << ") = " << dy << endl;
#endif
        }

#ifdef DEBUG
        cout << END_DEBUG;
#endif

        // SHOW OUTPUT
        if ((bx > MAX_BASE) || (by > MAX_BASE))
            cout << x << " is not equal to " << y << " in any base 2.." << MAX_BASE << endl;
        else
            cout << x << " (base " << bx << ") = " << y << " (base " << by << ")" << endl;

        // READ NEXT INPUT
        cin >> x >> y;
    }

    return 0;
}

/* @END_OF_SOURCE_CODE */

