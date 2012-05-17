
/* @JUDGE_ID:  40922FK  10071  C++  */
    
/**************************************************************************
 Solution to Problem 10071 - Back to High School Physics
 by: Francisco Dibar
 date: Dec-12-2004
**************************************************************************/

//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 

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

	int v, t;

	// v = a.t  =>  a = v/t
	// x = 1/2 a.tf^2		y  tf = 2t		
	//	=>  x = 1/2 v/t .(2t)^2		=> x = 2.v.t
	cin >> v >> t;
	while (!cin.eof()) {
		cout << 2*v*t << endl;
		cin >> v >> t;
	}

	return 0;
}
