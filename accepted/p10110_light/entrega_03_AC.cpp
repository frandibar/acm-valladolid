/* @JUDGE_ID:  40922FK  10110  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10110 - Light, more Light
 by: Francisco Dibar
 date: Oct-25-2005
**************************************************************************/

//#define DEBUG
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
	#include <fstream>
#endif 
#include <cmath>

#define START_DEBUG	"START DEBUG *******************************************************************\n"
#define END_DEBUG	"END DEBUG *********************************************************************\n"

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

	int64 n;
	cin >> n;
	while (n && !cin.eof()) {
		// PROCESS
		// square numbers have odd factors
		// the rest have even factors
		int64 r = sqrt(n);
		// SHOW OUTPUT
		cout << ((r*r == n) ? "yes" : "no") << endl;
		// READ NEXT INPUT
		cin >> n;
	}
		
	return 0;
}

/* @END_OF_SOURCE_CODE */

