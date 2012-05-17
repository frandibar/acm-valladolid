
/* @JUDGE_ID:  40922FK  10055  C++  */
    
/******************************************************************************
 Solution to Problem 10055 - Hashmat the brave warrior
 by: Francisco Dibar
 date: May-21-2004
******************************************************************************/

#include <iostream>
#include <fstream>
#include <queue>

//#define ONLINE_JUDGE 

// The base types 
#ifdef WIN32 
  typedef __int8            int8; 
  typedef __int16           int16; 
  typedef __int32           int32; 
  typedef __int64           int64; 
  typedef unsigned __int8   uint8; 
  typedef unsigned __int16  uint16; 
  typedef unsigned __int32  uint32; 
  typedef unsigned __int64  uint64; 
#else 
  typedef char                    int8; 
  typedef short                   int16; 
  typedef long                    int32; 
  typedef long long int           int64; 
  typedef unsigned char           uint8; 
  typedef unsigned short          uint16; 
  typedef unsigned long           uint32; 
  typedef unsigned long long int  uint64; 
#endif 

using namespace std;

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

	queue<int64> que_output;
	int64 x, y;

	cin >> x >> y;
	while (!cin.eof()) {
		if (x >= y) 
			que_output.push(x - y);
		else 
			que_output.push(y - x);
		cin >> x >> y;
	}

	while (!que_output.empty()) {
		x = que_output.front();
		que_output.pop();
		cout << x << endl;
	}

	return 0;
}

