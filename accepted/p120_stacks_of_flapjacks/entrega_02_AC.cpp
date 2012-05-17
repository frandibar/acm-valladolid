/* @JUDGE_ID:  40922FK  120  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 120 - Stacks of Flapjacks
 by: Francisco Dibar
 date: Jul-31-2006
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>    // sort

#ifdef DEBUG
    #define START_DEBUG	"START DEBUG ********************************************************************\n"
    #define END_DEBUG	"END DEBUG **********************************************************************\n"
    // g++-2.95 doesn't support asserts
    #define ASSERT(x,y)   if (!(x)) { std::cerr << "ASSERTION FAILED!: " << y << "\n"; exit(1); }
#endif

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


///////////////////////////////////////////////////////////////////////////
void print(const vector<int>& v)
// prints elements of vector v separated by space
{
        for (int i = 0; i < (int)v.size(); ++i)
            cout << v[i] << " ";
        cout << endl;
}

///////////////////////////////////////////////////////////////////////////
void flip(vector<int>& vDiameters, int aFlip)
// returns vDiameters after performing a flip at aFlip    
// a flip swaps paired elements between vDiameters[vDiameters.size - aFlip - 1] and vDiameters[0]
// aFlip = 1..vDiameters.size()
{
    int m = (vDiameters.size() - aFlip) / 2;
    int s = 0;
    for (int i = vDiameters.size() - aFlip; i > m; --i) {
        int aux = vDiameters[i];
        vDiameters[i] = vDiameters[s];
        vDiameters[s] = aux;
        s++;
    }
#ifdef DEBUG
    cout << "flip(" << aFlip << ")\t";
    print(vDiameters);
#endif
}

///////////////////////////////////////////////////////////////////////////
void getMoves(vector<int>& vDiameters, vector<int>& vMoves)
{
    vector<int> vSorted = vDiameters;
    std::sort(vSorted.begin(), vSorted.end());    // ascending order
#ifdef DEBUG
    cout << "Sorted:\t";
    print(vSorted);
    cout << "Start:\t";
    print(vDiameters);
#endif
    int ordered = 0;
    for (int i = (int)vSorted.size() - 1; i >= 0; --i) {
        // search for vSorted[i] in vDiameters
        for (int j = (int)vDiameters.size() - 1 - ordered; j >= 0; --j) {
            if (vSorted[i] == vDiameters[j]) {
                if (i != j) {
                    // it's not in place
                    // need to make 2 flips to put in place
                    if (j > 0) {
                        // it's not necessary to flip last one
                        vMoves.push_back(vDiameters.size() - j);
                        flip(vDiameters, vDiameters.size() - j); 
                    }
                    vMoves.push_back(ordered + 1);
                    flip(vDiameters, ordered + 1); 
                }
                ordered++;
                break;
            }
        }
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

    string line;
    getline(cin, line);
    while (!cin.eof()) {    

		// READ INPUT
        std::istringstream is(line);
        vector<int> vDiameters;
        int d;
        is >> d;
        while (!is.eof()) {
            vDiameters.push_back(d);
            is >> d;
        }

		// PROCESS
        vector<int> vMoves;
        getMoves(vDiameters, vMoves);

		// SHOW OUTPUT
        cout << line << endl;   // initial stack
        // moves
#ifdef DEBUG
        cout << "Moves:\t";
#endif        
        for (int i = 0; i < (int)vMoves.size(); ++i)
            cout << vMoves[i] << " ";
        cout << "0" << endl;

        getline(cin, line);
	}
		
#ifdef DEBUG
	cout << START_DEBUG;
    cout << "Testing flip" << endl;
    vector<int> v; 
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    for (int i = 0; i < (int)v.size(); ++i)
        cout << v[i] << " ";
    cout << endl;

    for (int k = 1; k <= 5; k++)
        flip(v, k);

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

