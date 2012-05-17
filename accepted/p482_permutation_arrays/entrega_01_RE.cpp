
/* @JUDGE_ID:  40922FK  482  C++  */
    
/******************************************************************************
 Solution to Problem 482 - Permutation Arrays
 by: Francisco Dibar
 date: May-11-2004
******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	string indices;
	string array;
	getline(cin, indices);
	getline(cin, array);
	
	vector<int> vec_indices;
	vector<string> vec_array;

	istringstream stream_indices(indices);
	istringstream stream_array(array);

	while (!stream_indices.eof() && !stream_array.eof()) {		
		int ind;
		string fl;
		stream_indices >> ind;
		stream_array >> fl;
		vec_indices.push_back(ind);
		vec_array.push_back(fl);
	}

	// mostrar la salida
	for (int i = 0; i < (int)vec_indices.size(); i++) {
		cout << vec_array[vec_indices[i]-1] << endl;
	}

	return 0;
}

