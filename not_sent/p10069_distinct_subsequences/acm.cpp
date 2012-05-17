/* @JUDGE_ID:  40922FK  10069  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10069 - Distinct Subsequences
 by: Francisco Dibar
 date: Aug-07-2005
**************************************************************************/

#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <string>

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

////////////////////////////////////////////////////////////////////////////////
inline int match(char a, char b)
{
	return ((a == b) ? 1 : 0);
}

////////////////////////////////////////////////////////////////////////////////
int lcs(const string& s, const string& t)
// returns the length of the longest common subsecuence
{
	vector< vector<int> > m(s.length());

	// fill matrix m
	// first row
	m[0].resize(t.length());
	m[0][0] = match(t[0], s[0]);
	for (int j = 1; j < (int)t.length(); j++)
		m[0][j] = m[0][j-1] + match(s[0], t[j]);

	// first column
	for (int i = 1; i < (int)s.length(); i++) {
		m[i].resize(t.length());
		m[i][0] = m[i-1][0] + match(s[i], t[0]);
	}

	// rest of the matrix
	for (int i = 1; i < (int)s.length(); i++) {
		for (int j = 1; j < (int)t.length(); j++) {
			m[i][j] = std::max( std::max(m[i-1][j-1], m[i-1][j]), m[i][j-1]) + match(t[j], s[i]);
		}           
	}

#ifdef DEBUG
    // show matrix
	cout << "  ";
	for (i = 0; i < (int)t.size(); i++)
		cout << t[i] << ' ';
	cout << endl;
	for (i = 0; i < (int)s.size(); i++) {
        for (int j = 0; j < (int)t.size(); j++) {
			if (j == 0) cout << s[i] << ' ';
            cout << m[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
#endif DEBUG

	return m[s.length()-1][t.length()-1];
}


////////////////////////////////////////////////////////////////////////////////
int count_distinct_subsequences(const string& s, const string& t)
// returns the length of the longest common subsecuence
{
	vector< vector<int> > m(s.length());

	// fill matrix m
	// first row
	m[0].resize(t.length());
	m[0][0] = match(t[0], s[0]);
	for (int j = 1; j < (int)t.length(); j++)
		m[0][j] = m[0][j-1] + match(s[0], t[j]);

	// first column
	for (int i = 1; i < (int)s.length(); i++) {
		m[i].resize(t.length());
		m[i][0] = m[i-1][0] + match(s[i], t[0]);
	}

	// rest of the matrix
	for (int i = 1; i < (int)s.length(); i++) {
		for (int j = 1; j < (int)t.length(); j++) {
			m[i][j] = std::max( std::max(m[i-1][j-1], m[i-1][j]), m[i][j-1]) + match(t[j], s[i]);
		}           
	}

#ifdef DEBUG
    // show matrix
	cout << "  ";
	for (i = 0; i < (int)t.size(); i++)
		cout << t[i] << ' ';
	cout << endl;
	for (i = 0; i < (int)s.size(); i++) {
        for (int j = 0; j < (int)t.size(); j++) {
			if (j == 0) cout << s[i] << ' ';
            cout << m[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
#endif DEBUG

	if (m[s.length()-1][t.length()-1] < (int)t.length())
		return 0;

	return 1;
}


///////////////////////////////////////////////////////////////////////////
//	MAIN PROGRAM
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redirect input and output
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new std::ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new std::ofstream("output.txt"))->rdbuf()); 
	#endif 

	int cases;

	cin >> cases;
	for (int k = 0; k < cases; k++) {
		// READ INPUT
		string s, t;
		cin >> s >> t;
#ifdef DEBUG
		cout << START_DEBUG;
		// PROCESS	
		// REVISAR!! cambiar n por bigint!
		int n = count_distinct_subsequences(t, s);
		cout << END_DEBUG;
#endif

		// SHOW OUTPUT
		cout << n << endl;
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

