/* @JUDGE_ID:  40922FK  482  C++  */
/* @BEGIN_OF_SOURCE_CODE */        
/**************************************************************************
 Solution to Problem 482 - Permutation Arrays
 by: Francisco Dibar
 date: Dec-20-2004
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

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

///////////////////////////////////////////////////////////////////////////
//	MAIN PROGRAM
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new std::ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new std::ofstream("output.txt"))->rdbuf()); 
	#endif 

	int cases;
	cin >> cases;

	string line;
	std::getline(cin, line);	// ignore line
	std::getline(cin, line);	

	for (int k = 0; k < cases; k++) {
		// read indexes
		std::getline(cin, line);	
		while (line.empty()) 
			std::getline(cin, line);	
		std::istringstream is(line);
		vector<int> vec_ind;
		while (!is.eof()) {
			int ind;
			is >> ind;
			if (!is.fail())
				vec_ind.push_back(ind);
		}
		
		// asume number of indexes = number of floats
		// read float as strings to avoid precision changes
		vector<string> vec_fl(vec_ind.size());
		for (int i = 0; i < (int)vec_ind.size(); i++)
			cin >> vec_fl[vec_ind[i]-1];

		// SHOW OUTPUT
		for (int i = 0; i < (int)vec_ind.size(); i++) 
			cout << vec_fl[i] << endl;

		if (k < (cases-1)) 
			cout << endl;
	}
   
	return 0;
}

