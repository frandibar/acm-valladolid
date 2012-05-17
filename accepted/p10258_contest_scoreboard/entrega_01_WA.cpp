/* @JUDGE_ID:  40922FK  10258  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10258 - Contest Scoreboard
 by: Francisco Dibar
 date: Jul-31-2005
**************************************************************************/

#define DEBUG 
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <sstream>	// istringstream
#include <string>
#include <vector>
#include <algorithm>		// sort

#define CORRECT			'C'
#define INCORRECT			'I'
#define CLARIF_REQUEST	'R'
#define UNJUDGED			'U'
#define ERRONEOUS			'E'

#define MAX_CONTESTANTS		100
#define NPROBLEMS				9

#define PENALTY			20

#define IND_CONTESTANT	0
#define IND_SENT			1
#define IND_CORRECT		2
#define IND_TIME			3

using namespace std;

///////////////////////////////////////////////////////////////////////////
class judge {
public:
	int sent;
	char status;
	int time;

	judge() {
		sent = 0;
		//status = '';
		time = 0;
	}
};

///////////////////////////////////////////////////////////////////////////
bool sortRes(vector<int> v, vector<int> s)
// devuelve true si v debe ir antes que s
{
	if (v[IND_CORRECT] > s[IND_CORRECT]) 
		return true;
	else if (v[IND_CORRECT] == s[IND_CORRECT]) {
		if (v[IND_TIME] > s[IND_TIME])
			return true;
		else if (v[IND_TIME] == s[IND_TIME])
			return (v[IND_CONTESTANT] < s[IND_CONTESTANT]);
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
///////////////////////////////////////////////////////////////////////////

// resultados inesperados aparecen si envia una solucion incorrecta
// luego de una correcta, o se envia dos resultados correctos
// al mismo problema

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	string line;
	int cases;
	cin >> cases;
	getline(cin, line);	// finish reading line
	getline(cin, line);	// skip blank line

	for (int k = 0; k < cases; k++) {
		// init mat de MAX_CONTESTANTS x NPROBLEMS
		vector< vector<judge> > matSub(MAX_CONTESTANTS+1);
		vector< vector<int> > matRes(MAX_CONTESTANTS+1);
		for (int i = 0; i <= MAX_CONTESTANTS; i++) {
			matSub[i].resize(NPROBLEMS+1);
			matRes[i].resize(IND_TIME+1);
		}

		// READ INPUT
		getline(cin, line);
		while (line.size() > 7) {
            int c, p, t;
			char s;
			istringstream is(line);
			is >> c >> p >> t >> s;
			if ((s == CORRECT) || (s == INCORRECT)) {
				matRes[c][IND_CONTESTANT] = c;
				matRes[c][IND_SENT] = 1;	// true
				if (s == CORRECT) {
					matRes[c][IND_CORRECT]++;
					matRes[c][IND_TIME] += t + matSub[c][p].sent * PENALTY;
				}
				matSub[c][p].sent++;
				matSub[c][p].status = s;
				matSub[c][p].time = t;
			}
			getline(cin, line);
		}
		
		// PROCESS
		// sort matRes
		sort(matRes.begin(), matRes.end(), sortRes);

		// SHOW RESULTS
		for (int i = 0; i <= MAX_CONTESTANTS; i++)
			if (matRes[i][IND_SENT] == 1)
				cout << matRes[i][IND_CONTESTANT] << " " << matRes[i][IND_CORRECT] << " " << matRes[i][IND_TIME] << endl;

		if (k < cases-1) 
			cout << endl;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

