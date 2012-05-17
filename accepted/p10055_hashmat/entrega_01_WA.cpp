
/* @JUDGE_ID:  40922FK  10055  C++  */
    
/******************************************************************************
 Solution to Problem 10055 - Hashmat the brave warrior
 by: Francisco Dibar
 date: May-21-2004
******************************************************************************/

#include <iostream>
#include <queue>

typedef unsigned long ulong;

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//	PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	queue<ulong> que_output;
	ulong x, y;

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

