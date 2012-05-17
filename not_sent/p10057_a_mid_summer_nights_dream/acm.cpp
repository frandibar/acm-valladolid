/* @JUDGE_ID:  40922FK  10057  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10057 - A mid-summer night's dream
 by: Francisco Dibar
 date: Aug-18-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <algorithm>		// sort

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

using namespace std;

///////////////////////////////////////////////////////////////////////////
long bf_distance(vector<int>& vec, int *pos)
// brute force method
// returns minimum distance to al points, at pos
{
	if (vec.size() > 0) {
		long	min = vec[vec.size()-1] * vec.size();	// max value
		for (int i = vec[0]; i <= vec[vec.size()-1]; i++) {
			int sum = 0;
			for (int j = 0; j < (int)vec.size(); j++) {
				sum += abs(vec[j] - i);
			}
			if (sum < min) {
				min = sum;
				*pos = i;
			}
		}
		return min;
	} else
		return 0;
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

	while (!cin.eof()) {

		// READ INPUT
		int values;
		cin >> values;
		vector<int> vec(values);
		for (int i = 0; i < values; i++)
			cin >> vec[i];
		
		// PROCESS
		sort(vec.begin(), vec.end());
		long	distanceL = 0, 
				distanceH = 0;
		for (int i = 0; i < values/2; i++)
			distanceL += vec[i];

		long middle;
		if (values % 2 == 0)
			middle = values/2;
		else
			middle = values/2 + 1;

		for (int i = middle; i < values; i++)
			distanceH += vec[i];

		long distance = distanceH - distanceL;

		// SHOW OUTPUT
		cout << distance << endl;

#ifdef DEBUG
	//	cout << START_DEBUG;
		int pos = 0;
		long bfd = bf_distance(vec, &pos);
		cout << bfd << " at " << pos << " by brute force " << endl;
	//	cout << END_DEBUG;
#endif

	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

