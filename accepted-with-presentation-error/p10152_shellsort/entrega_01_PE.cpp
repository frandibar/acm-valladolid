/* @JUDGE_ID:  40922FK  10152  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10152 - Shellsort
 by: Francisco Dibar
 date: Jul-29-2006
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>
#include <vector>

#ifdef DEBUG
    #define START_DEBUG	"START DEBUG ********************************************************************\n"
    #define END_DEBUG	"END DEBUG **********************************************************************\n"
    // g++-2.95 doesn't support asserts
    #define ASSERT(x,y)   if (!(x)) { std::cerr << "ASSERTION FAILED!: " << y << "\n"; exit(1); }
#endif

using std::cin;
using std::cout;
using std::endl;
using std::vector;

///////////////////////////////////////////////////////////////////////////
void sortTurtles(const vector<int>& vDesired, vector<int>& vMoves)
// returns in vMoves the moves necessary to convert vOriginal into vDesired    
{
    int iorig = (int)vDesired.size() - 1;
    for (int i = (int)vDesired.size() - 1; i >= 0; --i) {
        while ((vDesired[i] != iorig) && (iorig >= 0))
            iorig--;
        if (iorig < 0)
            vMoves.push_back(vDesired[i]);
        else
            iorig--;
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

	int cases;
	cin >> cases;

	for (int k = 0; k < cases; k++) {
		// READ INPUT
        int nturtles;
        cin >> nturtles;
        string line;
        getline(cin, line);     // ignore rest of line
        vector<string> vOriginal(nturtles);
        for (int i = 0; i < nturtles; ++i) {
            getline(cin, line);
            vOriginal[i] = line;
        }
        vector<int> vDesired(nturtles);     // stores the indexes of vOriginal, in the desired order
        for (int i = 0; i < nturtles; ++i) {
            getline(cin, line);
            // search for index of line in vOriginal
            for (int j = 0; j < nturtles; ++j) {
                if (vOriginal[j] == line)
                    vDesired[i] = j;
            }
        }

		// PROCESS
        vector<int> vMoves;
        sortTurtles(vDesired, vMoves);

		// SHOW OUTPUT
        for (int i = 0; i < (int)vMoves.size(); ++i)
            cout << vOriginal[vMoves[i]] << endl;

        // show empty line between cases
        if (k < cases - 1)
            cout << endl;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

