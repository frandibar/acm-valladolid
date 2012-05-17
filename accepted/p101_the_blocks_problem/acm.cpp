/* @JUDGE_ID:  40922FK  101  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 101 - The Blocks Problem
 by: Francisco Dibar
 date: Dec-17-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <string>
#include <sstream>

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

#define MOVE "move"
#define PILE "pile"
#define ONTO "onto"
#define OVER "over"
#define QUIT "quit"


using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

///////////////////////////////////////////////////////////////////////////
void process(const string& line, vector< vector<int> >& mat_blocks)
{
	std::istringstream is(line);
	string command, how;
	int a, b;
	is >> command >> a >> how >> b;
	
	if (a == b) return;	// illegal command

	// search for a and b
	int ai, aj, bi, bj;
	int found = 0;
	for (int i = 0; i < (int)mat_blocks.size(); i++) {
		for (int j = 0; j < (int)mat_blocks[i].size(); j++) {
			if (mat_blocks[i][j] == a) {
				ai = i;
				aj = j;
				found++;
			} else if (mat_blocks[i][j] == b) {
				bi = i;
				bj = j;
				found++;
			}
		}
		if (found == 2)
			break;
	}

	if (ai == bi) 
		return;	// illegal command

	if (command == MOVE) {
		// remove blocks on top of a
		for (int j = mat_blocks[ai].size()-1; j > aj; j--) {
			mat_blocks[mat_blocks[ai][j]].push_back(mat_blocks[ai][j]);
			mat_blocks[ai].pop_back();
		}
		if (how == ONTO) {
			// move a onto b
			// remove blocks on top of b
			for (int j = mat_blocks[bi].size()-1; j > bj; j--) {
				mat_blocks[mat_blocks[bi][j]].push_back(mat_blocks[bi][j]);
				mat_blocks[bi].pop_back();
			}
			mat_blocks[bi].push_back(a);
			mat_blocks[ai].pop_back();

		} else if (how == OVER) {
			// move a over b
			mat_blocks[bi].push_back(a);
			mat_blocks[ai].pop_back();
		}
	} else if (command == PILE) {
		if (how == ONTO) {
			// pile a onto b
			// remove blocks on top of b
			for (int j = mat_blocks[bi].size()-1; j > bj; j--) {
				mat_blocks[mat_blocks[bi][j]].push_back(mat_blocks[bi][j]);
				mat_blocks[bi].pop_back();
			}
			int removed = 0;
			for (int j = aj; j < (int)mat_blocks[ai].size(); j++) {
				mat_blocks[bi].push_back(mat_blocks[ai][j]);
				removed++;
			}

			for (int i = 0; i < removed; i++)
				mat_blocks[ai].pop_back();

		} else if (how == OVER) {
			// pile a over b
			int removed = 0;
			for (int j = aj; j < (int)mat_blocks[ai].size(); j++) {
				mat_blocks[bi].push_back(mat_blocks[ai][j]);
				removed++;
			}

			for (int i = 0; i < removed; i++)
				mat_blocks[ai].pop_back();

		}
	}
#ifdef DEBUG
	// show status
	cout << line << endl;
	for (int i = 0; i < (int)mat_blocks.size(); i++) {
		cout << i << ":";
		for (int j = 0; j < (int)mat_blocks[i].size(); j++) {
			cout << " " << mat_blocks[i][j];
		}
		cout << endl;
	}
#endif
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

	int blocks;
	cin >> blocks;

	vector< vector<int> > mat_blocks(blocks);
	// initialize mat_blocks
	for (int i = 0; i < blocks; i++)
		mat_blocks[i].push_back(i);

	// PROCESS
	string line;
	std::getline(cin, line);	// ignore line
	std::getline(cin, line);
#ifdef DEBUG
	cout << START_DEBUG;
#endif
	while ((line != QUIT) && !cin.eof()) {
		process(line, mat_blocks);
		// read next command
		std::getline(cin, line);
	}
#ifdef DEBUG
	cout << END_DEBUG;
#endif

	// SHOW OUTPUT
	for (int i = 0; i < blocks; i++) {
		cout << i << ":";
		for (int j = 0; j < (int)mat_blocks[i].size(); j++) {
			cout << " " << mat_blocks[i][j];
		}
		cout << endl;
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

