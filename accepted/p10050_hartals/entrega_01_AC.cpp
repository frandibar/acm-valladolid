/* @JUDGE_ID:  40922FK  10050  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10050 - Hartals
 by: Francisco Dibar
 date: Jan-01-2006
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

#define WORK	0
#define HARTAL 	1
#define FRIDAY 	6
#define SATURDAY 	7

using std::cin;
using std::cout;
using std::endl;
using std::vector;


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
		int days, parties;
		cin >> days >> parties;
		vector<int> vec_hp(parties);
		for (int i = 0; i < parties; i++)
			cin >> vec_hp[i];
		
		// PROCESS
		vector<int> vec_days(days+1);
		int lost = 0;
		for (int i = 0; i < parties; i++) {
			if (vec_hp[i] > 0) {
				for (int j = vec_hp[i]; j <= days; j += vec_hp[i]) {
					if ( (vec_days[j] == WORK) && (((j % 7) % 6) != 0) ) {
						lost++;
						vec_days[j] = HARTAL;
					}
				}
			}
		}

		// SHOW OUTPUT
#ifdef DEBUG
		cout << START_DEBUG;
		for (int i = 1; i < days; i++)
			if (vec_days[i] == HARTAL)
				cout << i << " ";
		cout << endl;
		cout << END_DEBUG;
#endif

		cout << lost << endl;
	}
		
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

