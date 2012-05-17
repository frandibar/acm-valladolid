
/* @JUDGE_ID:  40922FK  509  C++  */
    
/******************************************************************************
 Solution to Problem 509 - Morse Mismatches
 by: Francisco Dibar
 date: Jun-09-2004
******************************************************************************/

#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
//#define ONLINE_JUDGE 

using namespace std;

string vec_morse[] = { ".-",


////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redireccionar la entrada y salida
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new ifstream("input.txt"))->rdbuf()); 
		cout.rdbuf((new ofstream("output.txt"))->rdbuf()); 
	#endif 

	return 0;
}

