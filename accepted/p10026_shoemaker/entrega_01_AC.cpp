/* @JUDGE_ID:  40922FK  10026  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10026 - Shoemaker's Problem
 by: Francisco Dibar
 date: Jul-29-2006
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <algorithm>    // stable_sort

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

struct sJob {
    int id,
        delay,
        penalty;
};

///////////////////////////////////////////////////////////////////////////
bool cmpJobs(const sJob& j1, const sJob& j2)
// returns true if j1 should be performed before j2
{
    return (j1.delay * j2.penalty < j2.delay * j1.penalty);
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
        int njobs;
        cin >> njobs;
        if (njobs > 0) { 
            vector<sJob> vJobs(njobs);
            for (int i = 0; i < njobs; ++i) {
                sJob job;
                job.id = i + 1;
                cin >> job.delay >> job.penalty;
                vJobs[i] = job;
            }
            // PROCESS
            std::stable_sort(vJobs.begin(), vJobs.end(), cmpJobs);

            // SHOW OUTPUT
            for (int i = 0; i < njobs - 1; ++i)
                cout << vJobs[i].id << " ";
            cout << vJobs[njobs-1].id << endl;
        }
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

