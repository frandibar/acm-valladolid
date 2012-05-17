/* @JUDGE_ID:  40922FK  10047  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10047 - The Monocycle
 by: Francisco Dibar
 date: Sep-14-2006
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
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

const char START  = 'S';
const char TARGET = 'T';
const char BLOCK  = '#';
const char FREE   = '.';

///////////////////////////////////////////////////////////////////////////
int solve(const vector< vector<char> >& vMap)
// returns minimum time from START to TARGET, 0 if not possible    
{
    return 0;
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

	int n, m;
	cin >> n >> m;
    int ncase = 0;
    while ((n != 0) && (m != 0)) {
		// READ INPUT
        vector< vector<char> > vMap(n);
        for (int i = 0; i < n; ++i) {
            vMap[i].resize(m);
            for (int j = 0; j < n; ++j) {
                char c;
                cin >> c;
                if ((c != START) && (c != TARGET) && (c != BLOCK))
                    vMap[i][j] = FREE;
                else
                    vMap[i][j] = c;
            }
        }

		// PROCESS
        int time = solve(vMap);

		// SHOW OUTPUT
        ncase++;
        cout << "Case #" << ncase << endl;
        if (time > 0)
            cout << "minimum time = " << time << " sec" << endl;
        else
            cout << "destination not reachable" << endl;

        // READ NEXT INPUT
        cin >> n >> m;

        if ((n != 0) && (m != 0)) cout << endl;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

