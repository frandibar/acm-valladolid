/* @JUDGE_ID:  40922FK  481  C++  */
/* @BEGIN_OF_SOURCE_CODE */        
/**************************************************************************
 Solution to Problem 481 - What Goes Up
 by: Francisco Dibar
 date: Dec-12-2004
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <vector>
#include <algorithm>		// max_element

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

const char SEPARATOR =  '-';

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
		cin.rdbuf((new std::ifstream("input"))->rdbuf()); 
		cout.rdbuf((new std::ofstream("output"))->rdbuf()); 
	#endif 

	vector<int> vInput;
	int num;
	cin >> num;
	// READ INPUT
	while (!cin.eof()) {
		vInput.push_back(num);
		cin >> num;
	}

	// PROCESS
	// use dp to find sec max
	// TODO: esto es n^2!
	vector<int> vDp(vInput.size(), 1);	// init with 1
	for (int i = 1; i < (int)vInput.size(); i++) {
		for (int j = 0; j < i; j++) {
			if (vInput[j] < vInput[i]) {
				if (vDp[i] < vDp[j]+1)
					vDp[i] = vDp[j]+1;
			}
		}
	}

#ifdef DEBUG
	cout << START_DEBUG;
	// show vInput
	for (int i = 0; i < (int)vInput.size(); i++) 
		cout << vInput[i] << " ";
	cout << endl;
	// show vDp
	for (int i = 0; i < (int)vDp.size(); i++) 
		cout << vDp[i] << " ";
	cout << endl;
	cout << END_DEBUG;
#endif
	
	int maxSec = *std::max_element(vDp.begin(), vDp.end());
	cout << maxSec << endl << SEPARATOR << endl;

	// obtain sequence, obtained by showing vDp from back to beginning
	// printing element with maxSec and then in descending order
	// cant print directly because of reverse order
	vector<int> vSecMax(maxSec);
	int prox = maxSec;
	for (int i = (int)vInput.size()-1; (i >= 0) && (prox > 0); i--) {
		if (vDp[i] == prox) {
			prox--;
			vSecMax[prox] = vInput[i];
		}
	}

	// show sequence
	for (int i = 0; i < maxSec; i++) 
		cout << vSecMax[i] << endl;

	return 0;
}

/* @END_OF_SOURCE_CODE */
