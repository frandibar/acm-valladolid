/* @JUDGE_ID:  40922FK  382  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 382 - Perfection
 by: Francisco Dibar
 date: Dec-29-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <iomanip>		// setw

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

using std::cin;
using std::cout;
using std::endl;

///////////////////////////////////////////////////////////////////////////
long sum_of_divisors(long n)
{
	if (n == 1) return 1;

	long sum = 0;
	for (int i = 1; i <= n / 2; i++) {
		if (n % i == 0) {
			sum += i;
#ifdef DEBUG
			cout << i << " ";
#endif
		}
	}
#ifdef DEBUG
	cout << sum << endl;
#endif
	return sum;
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

	long n;
	cin >> n;
	cout << "PERFECTION OUTPUT" << endl;
	while ((n != 0) && !cin.eof()) {
		// PROCESS
		int sum = sum_of_divisors(n);
		 
		// SHOW OUTPUT
		cout << std::setw(5);
		cout << n << "  ";
		if (sum == n)
			cout << "PERFECT" << endl;
		else if (sum < n)
			cout << "DEFICIENT" << endl;
		else
			cout << "ABUNDANT" << endl;
		
		// READ NEXT INPUT
		cin >> n;
	}
	cout << "END OF OUTPUT" << endl;
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

