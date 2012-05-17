/* @JUDGE_ID:  40922FK  483  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 483 - Word Scramble
 by: Francisco Dibar
 date: Jul-21-2006
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

using std::cin;
using std::cout;
using std::endl;
using std::string;

///////////////////////////////////////////////////////////////////////////
void reverse(string& s, int from, int to)
// reverses s
{
    if (from < to) {
        int lb = int((to - from) / 2.0);
	    for (int i = 0; i <= lb; ++i) {
            // swap
            char t = s[from + i];
            s[from + i] = s[to - i];
            s[to - i] = t;
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
        // advance to first non whitespace
        int from = 0, 
            to = (int)line.length()-1;
        while ((line[from] == ' ') && from < (int)line.length())
            from++;

        for (int i = from; i < (int)line.length(); ++i) {
            if (line[i] == ' ') {
                to = i-1;
                reverse(line, from, to);
                // advance to first non whitespace
                from = i;
                to = (int)line.length()-1;
                while ((line[from] == ' ') && from < (int)line.length())
                    from++;
            }
		}
        if (from < to)
            reverse(line, from, to);

        // SHOW OUTPUT
		cout << line << endl;
        // READ NEXT INPUT
		getline(cin, line);
	}

#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif

	return 0;
}

/* @END_OF_SOURCE_CODE */
