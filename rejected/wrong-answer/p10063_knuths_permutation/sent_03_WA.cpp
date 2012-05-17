/* @JUDGE_ID:  40922FK  10063  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10063 - Knuth's Permutation
 by: Francisco Dibar
 date: Aug-27-2006
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
#include <string>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::queue;

////////////////////////////////////////////////////////////////////////////////
void permute(queue<string>& qPerm, const string& input)
// returns qPerm with all permutations of input    
{
    for (int i = 0; i < (int)input.length(); ++i) {
        string sc(1, input[i]);

        if (!qPerm.empty()) 
            while ((int)qPerm.front().length() <= i) {
                string line = qPerm.front();
                qPerm.pop();
                // perform all permutations for that line
                int chars = line.length();
                for (int j = 0; j <= chars; ++j) {
                    string res = line.substr(0, j);
                    res += sc;
                    res += line.substr(j, chars - j);
                    qPerm.push(res);
                }
            }
        else 
            qPerm.push(sc);
    }
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

	string input;
    getline(cin, input);
	while (!cin.eof()) {

#ifdef DEBUG
        cout << START_DEBUG;
        cout << "debugging input " << input << endl;
#endif

        // PROCESS
		queue<string> qPerm;
        permute(qPerm, input);

#ifdef DEBUG
        cout << END_DEBUG;
#endif

		// SHOW RESULTS
		while (!qPerm.empty()) {
			cout << qPerm.front() << endl;
			qPerm.pop();
		}
        
        // READ NEXT INPUT
        getline(cin, input);
		if (!cin.eof()) cout << endl;
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */
