/* @JUDGE_ID:  40922FK  10142  C++  */
/* @BEGIN_OF_SOURCE_CODE */
/**************************************************************************
 Solution to Problem 10142 - Australian Voting
 by: Francisco Dibar
 date: Dec-28-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <sstream>	// istringstream
#include <string>
#include <vector>

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

#define MAX_BALLOTS		1000
#define MAX_CANDIDATES	25
#define VOTES				0
#define ROUND				1

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

///////////////////////////////////////////////////////////////////////////
int process_ballots(int candidates, const vector<string>& vec_candidates, const vector< vector<int> >& mat_ballots,
						  vector< vector<int> >& mat_ballots_acum)
{
	// resize mat_ballots
	for (int i = 1; i <= candidates; i++)
		// i indicates candidate number
		// 1st index stores accumulated votes
		// 2nd index stores eliminated round
		mat_ballots_acum[i].resize(2); 

	int win_limit;
	// with even votes, win with v/2 + 1, else with (v+1)/2
	int ballots = (int)mat_ballots.size();
	if (ballots % 2 == 0)
		win_limit = ballots / 2 + 1;
	else
		win_limit = (ballots + 1) / 2;

	// load mat_ballots_acum with first vote
	int max_votes = 0;
	for (int i = 0; i < ballots; i++) {
		int candidate = mat_ballots[i][0];
		mat_ballots_acum[candidate][VOTES]++;
		// calculate max vote
		if (mat_ballots_acum[candidate][VOTES] > max_votes)
			max_votes = mat_ballots_acum[candidate][VOTES];
	}

	bool winner = (max_votes >= win_limit);
	int round = 0;
	while (!winner && (round < candidates)) {
		round++;
		// calculate minor amount of ballots
		int min_votes = ballots;	// initialize to max value
		for (int i = 1; i <= candidates; i++) {
			// if votes to this candidate are less than min_votes
			// and cantidate hasn't been eliminated
			if ((mat_ballots_acum[i][VOTES] < min_votes) && (mat_ballots_acum[i][ROUND] == 0))
				min_votes = mat_ballots_acum[i][VOTES];
		}
		// mark candidates with less votes as eliminated this round
		for (int i = 1; i <= candidates; i++) {
			// if votes to this candidate are equal to min_votes
			// and cantidate hasn't been eliminated
			if ((mat_ballots_acum[i][VOTES] == min_votes) && (mat_ballots_acum[i][ROUND] == 0))
				mat_ballots_acum[i][ROUND] = round;
		}
		// for these candidates, recount their votes for the other candidates
		for (int i = 1; i <= candidates; i++) {
			if (mat_ballots_acum[i][ROUND] == round) {
				// it's an eliminated candidate
				// find non eliminated candidates vote among those ballots
				// that had this candidate in 1st place
				for (int j = 0; j < ballots; j++) {
					if (mat_ballots[j][0] == i) {
						bool finish = false;
						for (int n = 1; (n < candidates) && !finish; n++)	
							// search from 2nd
							// if vote is to a non eliminated candidate or a
							// candidate eliminated this round
							if (mat_ballots_acum[ mat_ballots[j][n] ][ROUND] == 0) {
								mat_ballots_acum[ mat_ballots[j][n] ][VOTES]++;
								if (mat_ballots_acum[ mat_ballots[j][n] ][VOTES] >= win_limit)
									winner = true;
									finish = true;
								if (mat_ballots_acum[ mat_ballots[j][n] ][VOTES] > max_votes)
									max_votes = mat_ballots_acum[ mat_ballots[j][n] ][VOTES];
							}
					}
				}
			}
		}
	}

#ifdef DEBUG
	cout << START_DEBUG;
	// show mat_ballots_acum
	cout << "mat_ballots_acum" << endl;
	for (int i = 1; i <= candidates; i++) {
		cout << i << " ";
		for (int j = 0; j < (int)mat_ballots_acum[i].size(); j++)
			cout << mat_ballots_acum[i][j] << " ";
		cout << vec_candidates[i] << endl;
	}
	cout << END_DEBUG;
#endif

	return max_votes;
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
	string line;
	std::getline(cin, line);	// ignore rest of line
	std::getline(cin, line);	// skip blank line

	for (int k = 0; k < cases; k++) {
		// READ INPUT
		int candidates;
		cin >> candidates;
		std::getline(cin, line);	// ignore rest of line

		vector<string> vec_candidates(candidates+1);			
		// load vec_candidates with names
		for (int i = 1; i <= candidates; i++) {	// start index at 1!
			std::getline(cin, vec_candidates[i]);
		}

		// read ballots into mat_ballots
		int ballots = 0;
		vector< vector<int> > mat_ballots;
		std::getline(cin, line);
		while (!line.empty() && !cin.eof()) {
			std::istringstream is(line);
			vector<int> vec_ballots(candidates);
			vector<int> vec_check(candidates);
			for (int m = 0; m < candidates; m++)
				is >> vec_ballots[m];

			// use vec_check to see if each candidate was mentioned
			bool valid = true;
			for (int i = 0; i < candidates; i++)
				if (vec_check[ vec_ballots[i] - 1] == 1) {
					// repeated candidate
					valid = false;
					break;
				} else
					vec_check[ vec_ballots[i] - 1] = 1;

			for (int i = 0; i < candidates; i++)
				if (vec_check[i] == 0) {
					// a candidate was not mentioned
					valid = false;
					break;
				}

			if (valid) {
				mat_ballots.push_back(vec_ballots);
				ballots++;
			} // else ignore votes
			std::getline(cin, line);
		}
		
#ifdef DEBUG
	cout << START_DEBUG;
	// show mat_ballots
	cout << "mat_ballots" << endl;
	for (int i = 0; i < (int)mat_ballots.size(); i++) {
		cout << i << " ";
		for (int j = 0; j < (int)mat_ballots[i].size(); j++)
			cout << mat_ballots[i][j] << " ";
		cout << endl;
	}
	cout << END_DEBUG;
#endif

		// PROCESS
		vector< vector<int> > mat_ballots_acum(candidates+1);
		// mat_ballots_acum contains in index i the row 
		// corresponding to candidate i
		int max_votes = process_ballots(candidates, vec_candidates, mat_ballots, mat_ballots_acum);

		// SHOW OUTPUT
		// traverse mat_ballots_acum & show candidates with max_votes
		for (int c = 1; c <= candidates; c++) 
			if ((mat_ballots_acum[c][VOTES] == max_votes))
				cout << vec_candidates[c] << endl;

		// separate cases with blank line
		if (k < cases-1) cout << endl;
	}

#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif

	return 0;
}

/* @END_OF_SOURCE_CODE */

