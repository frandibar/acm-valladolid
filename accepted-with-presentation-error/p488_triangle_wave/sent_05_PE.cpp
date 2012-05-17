/* @JUDGE_ID:  40922FK  488  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/******************************************************************************
 Solution to Problem 488 - Triangle Wave
 by: Francisco Dibar
 date: Sep-04-2006
******************************************************************************/

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
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

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
        char amp;
		int frec;
		cin >> amp >> frec;

        // PROCESS
        ostringstream os;
        // output one wave to os
        // generating ascending part
        for (char a = '1'; a < amp; ++a)
            os << string(a - '0', a) << endl;
        
        // generating descending part
        for (char a = amp; a > '0'; --a)
            os << string(a - '0', a) << endl;
        

        // SHOW OUTPUT
        // frec waves separated by blank line
		for (int f = 0; f < frec - 1; ++f)
            cout << os.str() << endl;
		
        if (frec > 0)
            cout << os.str();

		if (k < ncases) cout << endl;
	}

#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */
