/* @JUDGE_ID:  40922FK  10188  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10188 - Automated Judge Script
 by: Francisco Dibar
 date: Aug-10-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <queue>
#include <string>
#include <cctype>		// isdigit, isspace

#define AC	0
#define PE	1
#define WA	2


using namespace std;

///////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	int lines;
	cin >> lines;
	string line;
	int run = 0;
	while (!cin.eof() && (lines != 0)) {
		string sc, ss;
		getline(cin, line);	// finish reading line
		run++;
		// READ INPUT
		for (int m = 0; m < lines; m++) {
			getline(cin, line);
			sc.append(line);
			sc.append("\n");
		}
		cin >> lines;
		getline(cin, line);	// finish reading line
		for (int m = 0; m < lines; m++) {
			getline(cin, line);
			ss.append(line);
			ss.append("\n");
		}

		// PROCESS
		int result = AC;
		long i = 0;
		if (sc.length() == ss.length())
			while ((sc[i] == ss[i]) && (i < (long)sc.length()))
				i++;
		else
			result = PE;

		if ((i != sc.length()) || (result != AC)) {
			// check for PE
			// i points to the first distinct char
			result = PE;
			long j = i;
			while ((i < (long)sc.length()) && (j < (long)ss.length())) {
				while ((i < (long)sc.length()) && !isdigit(sc[i])) 
					i++;
				while ((j < (long)ss.length()) && !isdigit(ss[j])) 
					j++;
				// now both are digits, compare them
				if (sc[i] != ss[j])
					result = WA;
				i++;
				j++;
			}
			// consider special case when i = sc.length and
			// j < ss.length
			if ((j < (long)ss.length()) && (result != WA))
				while ((j < (long)ss.length()) && (result != WA)) {
					if (isdigit(ss[j])) 
						result = WA;
					j++;
				}
		} 
		// else result = AC;

		// SHOW OUTPUT
		cout << "Run #" << run << ": ";
		switch (result) {
			case AC:	cout << "Accepted" << endl;
						break;
			case PE:	cout << "Presentation Error" << endl;
						break;
			case WA:	cout << "Wrong Answer" << endl;
						break;
			default: break;
		}

		cin >> lines;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

