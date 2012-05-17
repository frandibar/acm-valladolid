/* @JUDGE_ID:  40922FK  10194  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10194 - Football (aka Soccer)
 by: Francisco Dibar
 date: Aug-17-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>
#include <vector>
#include <algorithm>		// sort

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

#define NUM	0
#define PG	1
#define PE	2
#define PP	3
#define GF	4
#define GC	5

#define COLS 6		// GC + 1

using namespace std;

///////////////////////////////////////////////////////////////////////////
bool cmp_nocase(const string& s1, const string& s2)
// return true if s1 should go before s2 lexicographically
// ignoring case, 0..9..[aA]..[zZ]
// returns false if s1 = s2 
{
	string::const_iterator p1 = s1.begin();
	string::const_iterator p2 = s2.begin();

	while ((p1 != s1.end()) && (p2 != s2.end())) {
		if (toupper(*p1) != toupper(*p2))
			return (toupper(*p1) < toupper(*p2));
		++p1;
		++p2;
	}
	// one is a prefix of the other
	return (s1.size() < s2.size());
}

///////////////////////////////////////////////////////////////////////////
bool standings(const vector<int>& v1, const vector<int>& v2)
// return true if v1 should go before v2
{
	// ranking rules
	// 1. most points earned
	int points1 = 3 * v1[PG] + v1[PE];
	int points2 = 3 * v2[PG] + v2[PE];
	if (points1 != points2)
		return (points1 > points2);

	// 2. most wins
	if (v1[PG] != v2[PG])
		return (v1[PG] > v2[PG]);

	// most goal difference
	int goaldiff1 = v1[GF] - v1[GC];
	int goaldiff2 = v2[GF] - v2[GC];
	if (goaldiff1 != goaldiff2)
		return (goaldiff1 > goaldiff2);

	// most goals scored
	if (v1[GF] != v2[GF])
		return (v1[GF] > v2[GF]);

	// fewest games played
	int games1 = v1[PG] + v1[PE] + v1[PP];
	int games2 = v2[PG] + v2[PE] + v2[PP];
	if (games1 != games2)
		return (games1 < games2);

	// case insensitive lexicographic order
	if (v1[NUM] != v2[NUM])
		return (v1[NUM] < v2[NUM]);

	return false;
}

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

#ifdef DEBUG
		cout << START_DEBUG;
		cout << "lexicographic precedence (1 true, 0 false)" << endl;
		cout << "A " << cmp_nocase("A","B") << " B" << endl;
		cout << "A " << cmp_nocase("A","b") << " b" << endl;
		cout << "A " << cmp_nocase("A","a") << " a" << endl;
		cout << "a " << cmp_nocase("a","A") << " A" << endl;
		cout << "A " << cmp_nocase("A","1") << " 1" << endl;
		cout << END_DEBUG;
#endif

	int cases;
	cin >> cases;
	string line;
	getline(cin, line);	// ignore rest of line
	for (int k = 0; k < cases; k++) {
		// READ INPUT
		string championship;
		getline(cin, championship);
		int teams;
		cin >> teams;
		getline(cin, line);	// ignore rest of line
		vector<string> vecTeams(teams);
		vector< vector<int> > matData(teams);
		// read teams
		for (int i = 0; i < teams; i++) {
			getline(cin, line);
			vecTeams[i] = line;
			matData[i].resize(COLS);
			matData[i][NUM] = i;		// necessary for sorting
		}
		// this sort is necessary because of ranking rule 6 
		// (lexicographic order)
		sort(vecTeams.begin(), vecTeams.end(), cmp_nocase);

#ifdef DEBUG
		cout << START_DEBUG;
		for (int i = 0; i < teams; i++)
			cout << i << " " << vecTeams[i] << endl;
		cout << END_DEBUG;
#endif

		// read matches
		int matches;
		cin >> matches;
		getline(cin, line);	// ignore rest of line
		vector<string> vecMatches(matches);
		for (int i = 0; i < matches; i++) {
			getline(cin, line);
			vecMatches[i] = line;
			// parse match data
			int n1, n2, at;
			n1 = line.find("#");
			n2 = line.find_last_of("#");
			at = line.find("@");
			string team1 = line.substr(0, n1);
			string team2 = line.substr(n2 + 1, string::npos);
			string s1 = line.substr(n1 + 1, at - n1 - 1);
			string s2 = line.substr(at + 1, n2 - at - 1);
			// convert scores from string to int
			int score1, score2;
			if (s1.length() == 2)
				score1 = (s1[0]-'0')*10 + s1[1]-'0';
			else
				score1 = s1[0]-'0';

			if (s2.length() == 2)
				score2 = (s2[0]-'0')*10 + s2[1]-'0';
			else
				score2 = s2[0]-'0';

			// could also use map, but I don't since teams < 30
			int t1, t2;
			for (t1 = 0; (t1 < teams) && (vecTeams[t1] != team1); t1++)
				;
			for (t2 = 0; (t2 < teams) && (vecTeams[t2] != team2); t2++)
				;
			// load data
			matData[t1][GF] += score1;
			matData[t1][GC] += score2;
			matData[t2][GF] += score2;
			matData[t2][GC] += score1;
			if (score1 > score2) {
				matData[t1][PG]++;
				matData[t2][PP]++;
			} else if (score1 < score2) {
				matData[t1][PP]++;
				matData[t2][PG]++;
			} else {
				matData[t1][PE]++;
				matData[t2][PE]++;
			}
		}

		// PROCESS
		sort(matData.begin(), matData.end(), standings);

		// SHOW OUTPUT
		cout << championship << endl;
		for (int i = 0; i < teams; i++) {
			int points = 3*matData[i][PG] + matData[i][PE];
			int games = matData[i][PG] + matData[i][PE] + matData[i][PP];
			int goaldiff = matData[i][GF] - matData[i][GC];

			cout << i+1 << ") " << vecTeams[matData[i][NUM]] << " " << points << "p, " << games << "g, (" 
						<< matData[i][PG] << "-" << matData[i][PE] << "-" << matData[i][PP] 
						<< "), " << goaldiff << "gd (" << matData[i][GF] << "-" 
						<< matData[i][GC] << ")" << endl;

#ifdef DEBUG
//			cout << START_DEBUG;
			cout << matData[i][NUM] << " " << matData[i][PG] << " " << matData[i][PE] << " "
				<< matData[i][PP] << " " << matData[i][GF] << " " << matData[i][GC] << endl;
//			cout << END_DEBUG;
#endif
	
		}
		if (k < cases-1)
			cout << endl;
	}
		
	return 0;
}

/* @END_OF_SOURCE_CODE */

