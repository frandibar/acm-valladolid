/* @JUDGE_ID:  40922FK  591  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 591 - Box of Bricks
 by: Francisco Dibar
 date: Mar-21-2005
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 

#include <vector>

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

	int torres;
	int set = 0;
	cin >> torres;
	while ((torres != 0) && !cin.eof()) {
		if (set > 0) cout << endl;
		vector<int> vec_torres(torres);
		int boxes = 0;					// total de cajas
		set++;
		for (int i = 0; i < torres; i++) {
			cin >> vec_torres[i];
			boxes += vec_torres[i];
		}
		int h = boxes / torres;		// la altura final de cada torre
		int moves = 0;
		for (int j = 0; j < torres; j++)
			if (vec_torres[j] > h)
				moves += vec_torres[j] - h;
		
		// mostrar la salida
		cout << "Set #" << set << endl;
		cout << "The minimum number of moves is " << moves << "." << endl;
		cin >> torres;
	}

	return 0;
}

/* @END_OF_SOURCE_CODE */

