/* @JUDGE_ID:  40922FK  10024  C++  */
/* @BEGIN_OF_SOURCE_CODE */
/**************************************************************************
 Solution to Problem 10024 - Curling up the cube
 by: Francisco Dibar
 date: Dec-28-2004
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 

#ifdef DEBUG
    #define START_DEBUG	"**************************** START DEBUG *****************************\n"
    #define END_DEBUG	"***************************** END DEBUG ******************************\n"
    // g++-2.95 doesn't support asserts
    #define ASSERT(x,y)   if (!(x)) { std::cerr << "ASSERTION FAILED!: " << y << "\n"; exit(1); }
#endif

#include <iostream>
#ifndef ONLINE_JUDGE 
    #include <fstream>
#endif 
#include <cmath>        // pow

using std::cin;
using std::cout;
using std::endl;

const int COLS = 6;
const int ROWS = 6;
const int DIM  = 36;    // COLS * ROWS
const int DIMMAPS = 56;

// vMaps stores valid maps in binary representation
int vMaps[] = {     380,
                    497,
                    498,
                    500,
                    636,
                    726,
                    739,
                    753,
                    754,
                    756,
                    760,
                    876,
                    978,
                    994,
                    996,
                    1000,
                    1008,
                    1148,
                    1175,
                    1182,
                    1203,
                    1209,
                    1210,
                    1212,
                    1238,
                    1251,
                    1265,
                    1266,
                    1268,
                    1272,
                    1427,
                    1433,
                    1434,
                    1490,
                    1512,
                    1714,
                    1716,
                    1938,
                    2275,
                    2290,
                    2292,
                    2296,
                    2451,
                    2457,
                    2458,
                    2514,
                    2772,
                    3171,
                    3185,
                    3186,
                    3188,
                    3225,
                    3226,
                    3282,
                    3612,
                    3730 };

///////////////////////////////////////////////////////////////////////////
int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else        // found match
            return mid;
    }
    return -1;  // no match
}

///////////////////////////////////////////////////////////////////////////
//	MAIN PROGRAM
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
#ifndef ONLINE_JUDGE 
	// redirect input and output
    cin.rdbuf((new std::ifstream("input"))->rdbuf()); 
    cout.rdbuf((new std::ofstream("output"))->rdbuf()); 
#endif 

    int ncases;
    cin >> ncases;
    for (int k = 0; (k < ncases) && (!cin.eof()); ++k) {
        // READ INPUT
        int mBlock[ROWS][COLS];
        int ones = 0;       // stores amount of ones in block
        int xmin = COLS, xmax = 0, ymin = ROWS, ymax = 0;
        // load map in mBlock
        // get border coordinates
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                cin >> mBlock[i][j];
                if (mBlock[i][j] == 1) {
                    ones++;
                    if (i < ymin) ymin = i;
                    if (i > ymax) ymax = i;
                    if (j < xmin) xmin = j;
                    if (j > xmax) xmax = j;
                }
            }
        }

        // PROCESS
        // TODO: maybe some incorrect map gives a valid mapid
        bool ok = false;
        if (ones == 6) {
            long idMap = 0;
            double exp = 11;
            // calculate map id
            for (int i = ymin; i <= ymax; i++) {
                for (int j = xmin; j <= xmax; j++) {
                    if (mBlock[i][j] == 1)
                        // TODO: use shift instead of pow
                        idMap += (long)pow(2, exp);
                    exp--;
                }
            }
            ok = (binsearch(idMap, vMaps, DIMMAPS) != -1);
        }
#ifdef DEBUG
	cout << START_DEBUG;
	cout << END_DEBUG;
#endif
        // SHOW OUTPUT
        cout << (ok ? "correct" : "incorrect") << endl;
        
        // avoid last empty line
        if (k < ncases - 1) cout << endl;  
    }

    return 0;
}

/* @END_OF_SOURCE_CODE */

