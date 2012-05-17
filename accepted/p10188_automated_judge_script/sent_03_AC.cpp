/* @JUDGE_ID:  40922FK  10188  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10188 - Automated Judge Script
 by: Francisco Dibar
 date: Aug-21-2006
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

using std::cin;
using std::cout;
using std::endl;
using std::string;

enum eResult { AC, PE, WA };

///////////////////////////////////////////////////////////////////////////
eResult judge(const string& correct, const string& submitted)
{
    if (correct == submitted)
        return AC;

    // traverse correct and submitted, check if all numbers are correctly ordered
    string::size_type i = correct.find_first_of("0123456789");
    string::size_type j = submitted.find_first_of("0123456789");
    while (i != string::npos) {
        if (j == string::npos)
            return WA;
        if (correct[i] != submitted[j])
            return WA;
        i = correct.find_first_of("0123456789", i+1);
        j = submitted.find_first_of("0123456789", j+1);
    }
    if (j != string::npos)
        // found number in submission, not present in correct output
        return WA;

    return PE;
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

    int nlines;
    cin >> nlines;
    int run = 0;
    while (!cin.eof() && (nlines != 0)) {
        string line;
        getline(cin, line); // finish reading line
        run++;
        // READ INPUT
        string correct, submitted;
        for (int i = 0; i < nlines; ++i) {
            getline(cin, line);
            correct.append(line);
            correct.append("\n");
        }
        cin >> nlines;
        getline(cin, line); // finish reading line
        for (int i = 0; i < nlines; ++i) {
            getline(cin, line);
            submitted.append(line);
            submitted.append("\n");
        }

#ifdef DEBUG
        cout << START_DEBUG;
#endif
        // PROCESS
        eResult res = judge(correct, submitted);

#ifdef DEBUG
        cout << END_DEBUG;
#endif
        // SHOW OUTPUT
        cout << "Run #" << run << ": ";
        switch (res) {
            case AC:    cout << "Accepted" << endl;             break;
            case PE:    cout << "Presentation Error" << endl;   break;
            case WA:    cout << "Wrong Answer" << endl;         break;
        }

        // READ NEXT INPUT
        cin >> nlines;
    }

    return 0;
}

/* @END_OF_SOURCE_CODE */

