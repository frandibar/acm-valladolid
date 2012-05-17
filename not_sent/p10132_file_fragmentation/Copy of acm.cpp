/* @JUDGE_ID:  40922FK  10132  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10132 - File Fragmentation
 by: Francisco Dibar
 date: Aug-12-2005
**************************************************************************/

#define DEBUG 
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>
#include <vector>

#define MAX_LEN	300	// 256
#define MAX_FILES	150	// 144


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

	int cases;
	cin >> cases;
	string line;
	getline(cin, line);	// ignore rest of line
	getline(cin, line);	// ignore blank line
	for (int k = 0; k < cases; k++) {
		getline(cin, line);
		vector< vector<string> > matFiles(2*MAX_FILES);
		long sum = 0;
		int fragments = 0;
		// fragments of size n are pushed in matFiles[n]

		// READ INPUT
		while (!cin.eof() && !line.empty()) {
			// ignore repeated fragments
			int n = line.length();
			bool in = false;
			for (int i = 0; i < (int)matFiles[n].size() && !in; i++)
				if (matFiles[n][i] == line)
					in = true;

			if (!in) matFiles[n].push_back(line);

			sum += n;
			fragments++;
			getline(cin, line);		
		}
		
		// PROCESS		
		int res_length = sum / (fragments / 2);	// sum must be even
		string res;
		vector<string> vecPossible;
		vector<bool> vecTF;	// vecPossible[i] is still candidate?
		bool candidates = false;
		for (int i = 1; i < (int)matFiles.size(); i++) {
			if (matFiles[i].size() > 0 && !candidates) {
				candidates = true;
				for (int j = 0; j < (int)matFiles[i].size(); j++) {				
					for (int m = 0; m < (int)matFiles[i].size(); m++) {				
						//	make all possible solutions (max 8 distinct)
						// add candidate if not in vecPossible
						// a + b in doesn't imply b + a in
						if ((res_length - i != i) || ((res_length - i == i) && (j != m))) {
							string p1 = matFiles[i][j] + matFiles[res_length - i][m];
							string p2 = matFiles[res_length - i][m] + matFiles[i][j];
							bool inp1 = false;
							bool inp2 = false;
							for (int n = 0; n < (int)vecPossible.size() && (!inp1 || !inp2); n++) {
								if (vecPossible[n] == p1) inp1 = true;
								if (vecPossible[n] == p2) inp2 = true;
							}
							if (!inp1) {
								vecPossible.push_back(p1);
								vecTF.push_back(false);
							}
							if (!inp2 && (p1 != p2)) {
								vecPossible.push_back(p2);
								vecTF.push_back(false);
							}
						}
					}
				}
			}
			else if (candidates) {
				// got candidates, now discard them
			}
		}

#ifdef DEBUG
	for (int i = 0; i < (int)vecPossible.size(); i++)
		cout << i << ": " << vecPossible[i] << endl;
#endif

		// SHOW RESULTS
		cout << res << endl;

		if (k < cases-1) cout << endl;
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

