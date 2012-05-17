/* @JUDGE_ID:  40922FK  848  C++  */
/* @BEGIN_OF_SOURCE_CODE */        
/******************************************************************************
 Solution to Problem 848 - Fmt
 by: Francisco Dibar
 date: Jul-27-2006
******************************************************************************/
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
using std::string;

const int MAXLEN = 72;

////////////////////////////////////////////////////////////////////////////////
//	MAIN PROGRAM
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redirect input and output
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new std::ifstream("input"))->rdbuf()); 
		cout.rdbuf((new std::ofstream("output"))->rdbuf()); 
	#endif 

	string next;
	getline(cin, next);
	while (!cin.eof()) {
        // concatenate input lines into one long string, until a blank line is read (a whole paragraph)
        int i = next.find_last_not_of(' ');
		string in = next.substr(0, i + 1);	// ignore spaces at the end?
		while ((i != (int)string::npos) && !cin.eof()) {
			getline(cin, next);
            i = next.find_last_not_of(' ');
			// remove trialing spaces and append to in
			if (i != (int)string::npos) {
                // use += twice to avoid creation of temps
				in += " ";
                in += next.substr(0, i + 1);
            }
		}
		
#ifdef DEBUG
        cout << START_DEBUG;
        cout << "paragraph:" << endl << in << endl;
        cout << END_DEBUG;
#endif
		// manage paragraph (may be a line with spaces)
		// break 'in' into lines of MAXLEN
        string out;
		while (!in.empty()) {
			// convert line with only spaces to blank line
			if (in.find_first_not_of(' ') == string::npos) {				
				in = out = "";
			} else {
				if ((int)in.length() > MAXLEN) {
					// special case word containg more than MAXLEN chars
					int from = in.find_first_not_of(' '); 
					int to = in.substr(from, string::npos).find_first_of(' '); 
					if (to == (int)string::npos)
						to = in.length() - 1;
					if (to > MAXLEN) {
						// word contains more than MAXLEN chars
						if (from > 0)
							// white space before word exists, print blank line
							cout << endl;
						out = in.substr(from, to);	// word
						in = in.substr(to + 1, string::npos);
					} else {
						out = in.substr(0, MAXLEN + 1);
						// leave out last cut word
						out = out.substr(0, out.find_last_of(' '));
						// if only spaces are left then print blank line
						if (out.find_first_not_of(' ') == string::npos)
							cout << endl;
						// leave out trialing spaces
						to = out.find_last_not_of(' ');
						if (to != (int)string::npos) {
							out = out.substr(0, to + 1);
							// cut _in_
							in = in.substr(to + 1, string::npos);
						} else
							in = in.substr(out.length()+1, string::npos);
						// ignore 1 space at beginning
						in = in.substr(1, string::npos);
					}
				} else {
					// leave out trialing spaces
					int to = in.find_last_not_of(' ') + 1;
					out = in.substr(0, to);
					in = "";		// finish condition
				}
			}
			if (!out.empty())
				cout << out << endl;
		}
		out = next;
		// hack to avoid additional line at the end
		if (!cin.eof() && (out.find_first_not_of(' ') == string::npos)) 
            cout << endl;

		if (!cin.eof())
			getline(cin, next);
		
	}

#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	return 0;
}

/* @END_OF_SOURCE_CODE */

