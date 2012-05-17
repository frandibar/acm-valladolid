/* @JUDGE_ID:  40922FK  848  C++  */
/* @BEGIN_OF_SOURCE_CODE */        
/******************************************************************************
 Solution to Problem 848 - Fmt
 by: Francisco Dibar
 date: Aug-13-2005
******************************************************************************/
//#define DEBUG 
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>

using std::cin;
using std::cout;
using std::string;

const int MAX_LEN = 72;

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

	string in, out, next;
	getline(cin, next);
	while (!cin.eof()) {
		in = next;	// REVISAR si ignorar espacios al final
		// while chars are read
		while ((next.find_last_not_of(' ') != string::npos) && !cin.eof()) {			
			getline(cin, next);
			// remove trialing spaces and append to in
			if (next.find_last_not_of(' ') != string::npos)
				in += " " + next.substr(0, next.find_last_not_of(' ') + 1);
		}
		
		// manage paragraph (may be a line with spaces)
		// break _in_ into lines of MAX_LEN
		while (!in.empty()) {
			// convert line with only spaces to blank line
			if (in.find_first_not_of(' ') == string::npos) {				
				in = "";
				out = "";
			} else {
				if ((int)in.length() > MAX_LEN) {
					// special case word containg more than MAX_LEN chars
					int from = in.find_first_not_of(' '); 
					int to = in.substr(from, string::npos).find_first_of(' '); 
					if (to == (int)string::npos)
						to = in.length() - 1;
					if (to > MAX_LEN) {
						// word contains more than MAX_LEN chars
						if (from > 0)
							// white space before word exists, print blank line
							cout << endl;
						out = in.substr(from, to);	// word
						in = in.substr(from + to + 1, string::npos);
					} else {
						out = in.substr(0, MAX_LEN);
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
		if (!cin.eof())
			getline(cin, next);
		
		// hack to avoid additional line at the end
		if (!cin.eof())
			if (out.find_first_not_of(' ') == string::npos) 
				cout << endl;
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

