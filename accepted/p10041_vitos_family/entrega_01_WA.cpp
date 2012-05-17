/* @JUDGE_ID:  40922FK  10041  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10041 - Vito's Family
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

	int cases;
	cin >> cases;

	for (int k = 0; k < cases; k++) {

		// READ INPUT
		int houses;
		cin >> houses;
		vector<int> vecHouses(houses);
		for (int i = 0; i < houses; i++)
			cin >> vecHouses[i];
		
		// PROCESS
		long	distanceL = 0, 
				distanceH = 0;
		for (int i = 0; i < houses/2; i++)
			distanceL += vecHouses[i];

		long middle;
		if (houses % 2 == 0)
			middle = houses/2;
		else
			middle = houses/2 + 1;

		for (int i = middle; i < houses; i++)
			distanceH += vecHouses[i];

		long distance = distanceH - distanceL;

		// SHOW OUTPUT
		cout << distance << endl;

#ifdef DEBUG
	//	cout << START_DEBUG;
		int pos = 0;
		long bfd = bf_distance(vecHouses, &pos);
		cout << bfd << " at " << pos << " by brute force " << endl;
	//	cout << END_DEBUG;
#endif

	}
	return 0;
}

/* @END_OF_SOURCE_CODE */

