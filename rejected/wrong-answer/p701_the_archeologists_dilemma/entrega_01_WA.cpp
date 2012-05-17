/* @JUDGE_ID:  40922FK  701  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 701 - The Archeologist's Dilemma
 by: Francisco Dibar
 date: Nov-16-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <string>

#define DIM 68

#define START_DEBUG	"START DEBUG ********************************************************************\n"
#define END_DEBUG	"END DEBUG **********************************************************************\n"

using namespace std;

// v[i] contains the first half of the digits corresponding to 2^i
string v[] = {
				"",
				"",
				"",
				"",
				"",
				"",
				"",
				"1",
				"2",
				"5",
				"1",
				"2",
				"4",
				"8",
				"16",
				"32",
				"65",
				"13",
				"26",
				"52",
				"104",
				"209",
				"419",
				"838",
				"167",
				"335",
				"671",
				"1342",
				"2684",
				"5368",
				"1073",
				"2147",
				"4294",
				"8589",
				"17179",
				"34359",
				"68719",
				"13743",
				"27487",
				"54975",
				"109951",
				"219902",
				"439804",
				"879609",
				"175921",
				"351843",
				"703687",
				"1407374",
				"2814749",
				"5629499",
				"1125899",
				"2251799",
				"4503599",
				"9007199",
				"18014398",
				"36028797",
				"72057594",
				"14411518",
				"28823037",
				"57646075",
				"115292150",
				"230584300",
				"461168601",
				"922337203",
				"184467440",
				"368934881",
				"737869762",
				"1475739525" };

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

	string n;	// read number as string
	cin >> n;
	while (!cin.eof()) {
		// PROCESS
		// find if n is contained in some v[i]
		int i;
		for (i = 7; i < DIM; i++) {	// first 6 are empty
			if (n == v[i].substr(0, n.length())) {
				break;
			}
		}
				
		// SHOW OUTPUT
		if (i < DIM)
			cout << i << endl;
		else
			cout << "no power of 2" << endl;

		// READ NEXT INPUT
		cin >> n;
	}
		
#ifdef DEBUG
	cout << START_DEBUG;

	cout << END_DEBUG;
#endif
	
	return 0;
}

/* @END_OF_SOURCE_CODE */

