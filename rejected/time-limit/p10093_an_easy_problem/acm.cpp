/* @JUDGE_ID:  40922FK  10093  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/******************************************************************************
 Solution to Problem 10093 - An Easy Problem!
 by: Francisco Dibar
 date: Aug-16-2006
******************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
    #include <fstream>
#endif 
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

///////////////////////////////////////////////////////////////////////////
long toDecimal(const string& num, unsigned int base)
// returns num expressed in base base to decimal
{
    long res = 0;
    long exp = 1;
    for (int i = (int)num.size() - 1; i >= 0; --i) {
        if (num[i] <= '9')
            res += (num[i] - '0') * exp;
        else if (num[i] <= 'Z')
            res += (num[i] - 'A' + 10) * exp;
        else   // assume num[i] <= 'y'
            res += (num[i] - 'a' + 10 + 1 + 'Z' - 'A') * exp;
        exp *= base;
    }
#ifdef DEBUG
    cout << num << " in base " << base << " = " << res << " in decimal" << endl;
#endif
    return res;
}

///////////////////////////////////////////////////////////////////////////
int minBase(const string& s)
{
    char max = 0;
    // find max char in s
    for (int i = 0; i < (int)s.size(); ++i) 
        if (s[i] > max) max = s[i];

    // set corresponding base to max, 2..9A..Za..y
    int base = 0;
    if (max == '0') base = 2;
    else if ((max >  '0') && (max <= '9')) base = max - '0' + 1;
    else if ((max >= 'A') && (max <= 'Z')) base = max - 'A' + 10 + 1;
    else if ((max >= 'a') && (max <= 'z')) base = max - 'a' + 10 + 1 + 'Z' - 'A' + 1;

#ifdef DEBUG
    cout << s << " can be expressed from base " << base << endl;
#endif

    while (toDecimal(s, base) % (base-1) != 0)
        base++;

    return base;
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

    string R;
    cin >> R;
    while (!cin.eof()) {

#ifdef DEBUG
        cout << START_DEBUG;
        cout << "solving for R = " << R << endl;
#endif
        // PROCESS
        int N = minBase(R);

#ifdef DEBUG
        cout << END_DEBUG;
#endif

        // SHOW OUTPUT
        if (N == 0)
            cout << "such number is impossible!" << endl;
        else
            cout << N << endl;

        // READ NEXT INPUT
        cin >> R;
    }

    return 0;
}

/* @END_OF_SOURCE_CODE */

/*
   Method to solve:

   read input R
   search for max char in R, this gives us N, the minimum base R can be expressed in
   convert R to decimal, and check if it divides N-1
   if true, then finish, else repeat previous step incrementing R

   */
   
