/* @JUDGE_ID:  40922FK  nnn  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem nnn - name
 by: Francisco Dibar
 date: Sep-01-2006
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

using std::cin;
using std::cout;
using std::endl;


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

	for (int k = 0; k < ncases; ++k) {

		// READ INPUT

		// PROCESS

		// SHOW OUTPUT

	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

