
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
struct res {
	ulong resultado;
	char signo;
};

int main(int argc, char *argv[])
{
	queue<res> que_output;
	ulong x, y;
	res output;

	cin >> x >> y;
	while (!cin.eof()) {
		if (x >= y) {
			output.resultado = x - y;
			output.signo = '+';
		} else {
			output.resultado = y - x;
			output.signo = '-';
		}
		que_output.push(output);
		cin >> x >> y;
	}

	while (!que_output.empty()) {
		output = que_output.front();
		que_output.pop();
		if (output.signo == '-')
			cout << output.signo;
		cout << output.resultado << endl;
	}

	return 0;
}

